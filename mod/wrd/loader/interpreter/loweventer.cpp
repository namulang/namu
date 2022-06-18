#include "loweventer.hpp"
#include "bison/lowparser.hpp"
#include "../../ast.hpp"
#include "../../ast/mgd/mgdFunc.hpp"
#include "../../builtin/primitive.hpp"

namespace wrd {

    using std::string;
    WRD_DEF_ME(loweventer)

    namespace {
        string merge(const narr& dotname) {
            string ret;
            for(auto& e : dotname)
                ret += e.cast<std::string>();
            return ret;
        }
    }

    wint me::_onScan(YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner) {
        int tok = _mode->onScan(*this, val, loc, scanner);
        if (_isIgnoreWhitespace && tok == NEWLINE) return SCAN_AGAIN;
        _isIgnoreWhitespace = false;

        switch(tok) {
            case SCAN_MODE_NORMAL: setScan<normalScan>(); return SCAN_AGAIN;
            case SCAN_MODE_INDENT: setScan<indentScan>(); return SCAN_AGAIN;
            case SCAN_MODE_INDENT_IGNORE: _isIgnoreWhitespace = true; return SCAN_AGAIN;
            case SCAN_MODE_END: tok = 0; // == yyterminate();
        }

        return tok;
    }

    wint me::onScan(loweventer& ev, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner, wbool& isBypass) {
        int tok;
        do
            // why do you put redundant _onScan() func?:
            //  because of definately, clang++ bug. when I use continue at switch statement inside of
            //  do-while loop here, it doesn't work like usual 'continue' keyword does, but it does like
            //  'break'.
            tok = _onScan(val, loc, scanner);
        while(tok == SCAN_AGAIN);

        return tok;
    }

    wint me::onEndOfFile() {
        WRD_DI("tokenEvent: onEndOfFile() indents.size()=%d", _indents.size());
        if(_indents.size() <= 1)
            _dispatcher.add(SCAN_MODE_END);
        else
            _dispatcher.addFront(onDedent(_indents.front(), SCAN_MODE_END));

        WRD_DI("tokenEvent: onEndOfFile: finalize by adding 'NEWLINE', then dispatch end-of-file.");
        return NEWLINE;
    }

    wint me::onIndent(wcnt col, wint tok) {
        WRD_DI("tokenEvent: onIndent(col: %d, tok: %d) indents.size()=%d", col, tok, _indents.size());
        _indents.push_back(col);
        _dispatcher.add(tok);
        return INDENT;
    }

    wint me::onDedent(wcnt col, wint tok) {
        WRD_DI("tokenEvent: onDedent(col: %d, tok: %d) indents.size()=%d", col, tok, _indents.size());

        _indents.pop_back();
        wint now = _indents.back();
        if(now < col)
            onSrcWarn(errCode::WRONG_INDENT_LV, col, now, now);

        while(_indents.back() > col) {
            WRD_DI("tokenEvent: onDedent: indentlv become %d -> %d", _indents.back(), _indents[_indents.size()-2]);
            _indents.pop_back();
            _dispatcher.add(DEDENT);
        }

        _dispatcher.add(tok);
        return DEDENT;
    }

    void me::onNewLine() {
        WRD_DI("tokenEvent: onNewLine: _isIgnoreWhitespace=%s, _indents.size()=%d",
            _isIgnoreWhitespace ? "true" : "false", _indents.size());
        if(!_isIgnoreWhitespace && _indents.size() >= 1)
            _dispatcher.add(SCAN_MODE_INDENT);
    }

    wchar me::onScanUnexpected(const wchar* token) {
        onSrcErr(errCode::UNEXPECTED_TOK, token);
        return token[0];
    }

    wint me::onIgnoreIndent(wint tok) {
        WRD_DI("tokenEvent: onIgnoreIndent(%d)", tok);
        _dispatcher.add(SCAN_MODE_INDENT_IGNORE);
        return tok;
    }

    void me::onEndParse() {
        area& area = *_srcArea;
#if WRD_IS_DBG
        const point& pt = area.start;
        WRD_DI("tokenEvent: onEndParse(%d,%d)", pt.row, pt.col);
#endif
        area.rel();
    }

    node* me::onPack(const narr& dotname) {
        WRD_DI("tokenEvent: onPack(%s)", merge(dotname).c_str());
        obj* pak = &_slot->getPack();

        // pack syntax rule #1:
        //  if there is no specified name of pack, I create an one.
        std::string firstName = dotname[0].cast<std::string>();
        if(nul(pak))
            _slot->setPack(pak = new obj(manifest(firstName));

        const std::string& realName = pak->getManifest().name;
        if(realName != firstName)
            return onErr(errCode::PACK_NOT_MATCH, firstName.c_str(), realName.c_str()), pak;

        // pack syntax rule #2:
        //  middle name automatically created if not exist.
        //  on interpreting 'mypack' pack, user may uses 'pack' keyword with dotted-name.
        //  for instance,
        //      'pack mypack.component.ui'
        //  in this scenario, mypack instance should be created before. and component sub
        //  pack object can be created in this parsing keyword.
        node* e = pak;
        for(int n=1; n < dotname.len(); n++) {
            const std::string& name = dotname[n].cast<std::string>();
            node* sub = &e->sub(name);
            if(nul(sub))
                e->subs().add(name, sub = new obj());
            e = sub;
        }

        _subpack.bind(e);
        return e;
    }

    node* me::onPack() {
        WRD_DI("tokenEvent: onPack()");

        onWarn(errCode::NO_PACK);

        slot* newSlot = &_slot.get();
        if(nul(newSlot))
            _slot.bind(newSlot = new slot(manifest());

        const std::string& name = _slot->getManifest().name;
        if(name != manifest::DEFAULT_NAME)
            return onErr(errCode::PACK_NOT_MATCH, manifest::DEFAULT_NAME, name.c_str()), newPack;

        _subpack.bind(newSlot->getPack()); // this is a default pack containing name as '{default}'.
        return *_subpack;
    }

    blockExpr* me::onBlock() {
        WRD_DI("tokenEvent: onBlock()");
        return new blockExpr();
    }

    blockExpr* me::onBlock(blockExpr& blk, node& stmt) {
        WRD_DI("tokenEvent: onBlock()");
        if(nul(blk))
            return onSrcErr(errCode::IS_NULL, "blk"), onBlock();
        blk.getStmts().add(stmt);
        WRD_DI("tokenEvent: onBlock().len=%d", blk.getStmts().len());
        return &blk;
    }

    defBlock* me::onDefBlock() {
        WRD_DI("tokenEvent: onDefBlock()");
        return new defBlock();
    }

    defBlock* me::onDefBlock(defBlock& s, node& candidate) {
        WRD_DI("tokenEvent: onDefBlock(candidate=%s)", candidate.getType().getName().c_str());
        if(nul(s))
            return onSrcErr(errCode::IS_NULL, "s"), onDefBlock();

        expr* e = &candidate.cast<expr>();
        if(nul(e))
            return onSrcErr(errCode::PARAM_HAS_VAL, candidate.getType().getName().c_str()), onDefBlock();

        defVarExpr& defVar = e->cast<defVarExpr>();
        if(!nul(defVar)) {
            s.asScope->add(defVar.getParam().getName(), *defVar.getParam().getOrigin());
            return &s;
        }
        defAssignExpr& defAssign = e->cast<defAssignExpr>();
        if(!nul(defAssign)) {
            s.asScope->add(defAssign.getSubName(), nullptr);
            s.asPreCtor->add(new assignExpr(*new getExpr(defAssign.getSubName()), defAssign.getRight()));
            return &s;
        }

        s.asScope->add(_onPopName(*e), e);
        return &s;
    }

    expr* me::onDefVar(const std::string& name, const node& origin) {
        WRD_DI("tokenEvent: onDefVar(%s, %s)", origin.getType().getName().c_str(), name.c_str());
        return new defVarExpr(*new param(name, origin));
    }

    void me::onSrcArea(area& area) {
        _srcArea = &area;
    }

    void me::_onRes(err* new1) {
        new1->log();
        _report->add(new1);
    }

    params me::_convertParams(const narr& exprs) {
        params ret;
        for(auto& expr: exprs) {
            defVarExpr& cast = expr.cast<defVarExpr>();
            if(nul(cast)) return onSrcErr(errCode::NOT_EXPR, expr.getType().getName().c_str()), ret;
            if(nul(cast.getParam())) return onSrcErr(errCode::PARAM_HAS_VAL), ret;

            ret.add(cast.getParam().clone());
        }

        return ret;
    }

    mgdFunc* me::onFunc(const std::string& name, const narr& exprs, const node& evalObj, const blockExpr& blk) {
        const wtype& evalType = evalObj.getType();
        WRD_DI("tokenEvent: onFunc: %s(...[%x]) %s: blk.len()=%d", name.c_str(), &exprs,
                evalType.getName().c_str(), blk.getStmts().len());

        mgdFunc* ret = new mgdFunc(_convertParams(exprs), evalType, blk);
        _onPushName(name, *ret);
        return ret;
    }

    narr* me::onList() {
        narr* ret = new narr();
        WRD_DI("tokenEvent: onList()=%x", ret);
        return ret;
    }
    narr* me::onList(node* newExpr) {
        narr* ret = new narr(*newExpr);
        WRD_DI("tokenEvent: onList(%s[%x])=%x", newExpr->getType().getName().c_str(), newExpr, ret);
        return ret;
    }
    narr* me::onList(narr& list, node* newExpr) {
        WRD_DI("tokenEvent: onList(list[%x], %s[%x])", &list, newExpr->getType().getName().c_str(), newExpr);
        list.add(newExpr);
        return &list;
    }

    obj* me::onDef(const std::string& name, defBlock& blk) {
        WRD_DI("tokenEvent: onDef(%s, defBlock[%x])", name.c_str(), &blk);

        obj& ret = *new obj();
        _onInjectObjSubs(ret, blk);
        _onPushName(name, ret);
        return &ret;
    }

    void me::onCompilationUnit(obj& subpack, defBlock& blk) {
        WRD_DI("tokenEvent: onCompilationUnit(%x, defBlock[%x])", &subpack, &blk);
        if(nul(subpack)) {
            onErr(errCode::NO_PACK_TRAY);
            return;
        }

        _onInjectObjSubs(subpack, blk);
    }

    wbool me::_onInjectObjSubs(obj& it, defBlock& blk) {
        WRD_DI("tokenEvent: _onInjectObjSubs(%s, defBlock[%x])", obj.getType().getName().c_str(), &blk);
        if(nul(it)) return false;

        bicontainable& share = it.getShares().getContainer();
        bicontainable& own = it.getOwns();
        for(auto e=blk.asScope->begin(); e ;++e) {
            bicontainable& con = nul(e.getVal<func>()) ? own : share;
            con.add(e.getKey(), *e);
        }

        _onInjectDefaultCtor(it);
        return _onPastePreCtors(it, *blk.asPreCtor);
    }

    wbool me::_onInjectDefaultCtor(obj& it) {
        wbool hasCtor = nul(it.sub(baseObj::CTOR_NAME));
        WRD_DI("tokenEvent: _onInjectDefaultCtor(%s, has=%d)", obj.getType().getName().c_str(), hasCtor);
        if(hasCtor) return false;

        class _wout mgdDefaultCtor : public mgdFunc {
            WRD(CLASS(mgdDefaultCtor, mgdFunc))

        public:
            mgdDefaultCtor(const node& org) {
                getBlock().getStmts().add(new makeExpr(org));
            }
        };
        it.subs().add(*new mgdDefaultCtor(it.getOrigin()));
        return true;
    }

    wbool me::_onPastePreCtors(obj& it, narr& preCtor) {
        WRD_DI("tokenEvent: onPastePreCtors(%s, %x)", it.getType().getName().c_str(), &preCtor);

        auto e = it.subs().iterate(obj::CTOR_NAME);
        while(e) {
            mgdFunc& f = e.getVal<mgdFunc>();
            if(!nul(f)) {
                auto stmts = f.getBlock().getStmts();
                stmts.add(stmts.begin(), preCtor);
            }

            ++e;
        }

        return true;
    }

    returnExpr* me::onReturn() {
        WRD_DI("tokenEvent: onReturn()");

        return new returnExpr();
    }
    returnExpr* me::onReturn(node& exp) {
        WRD_DI("tokenEvent: onReturn(%s)", exp.getType().getName().c_str());

        return new returnExpr(exp);
    }

    node* me::onName(const std::string& name) {
        return new wStr(name);
    }

    narr* me::onDotName(const node& name) {
        narr* ret = new narr();
        ret->add(name);
        return ret;
    }
    narr* me::onDotName(narr& names, const node& name) {
        names.add(name);
        return &names;
    }

    node* me::onGet(const std::string& name) {
        WRD_DI("tokenEvent: onGet(%s)", name.c_str());

        return new getExpr(name);
    }
    node* me::onGet(const std::string& name, const narr& args) {
        WRD_DI("tokenEvent: onGet(%s, %d)", name.c_str(), args.len());

        return new getExpr(name, args);
    }
    node* me::onGet(node& from, const std::string& name, const narr& args) {
        WRD_DI("tokenEvent: onGet(%s, %s, %d)", from.getType().getName().c_str(),
                name.c_str(), args.len());

        return new getExpr(from, name, args);
    }

    void me::_onPushName(const std::string& name, node& n) {
        _nameMap[&n] = name;
    }

    std::string me::_onPopName(node& n) {
        std::string ret = _nameMap[&n];
        _nameMap.erase(&n);
        return ret;
    }

    runExpr* me::onRunExpr(const std::string& name, const narr& args) {
        WRD_DI("tokenEvent: onRunExpr(%s, narr[%d])", name.c_str(), args.len());

        return new runExpr(nulOf<node>(), name, args);
    }

    // @param from  can be expr. so I need to evaluate it through 'as()'.
    runExpr* me::onFillFromOfFuncCall(const node& me, runExpr& to) {
        WRD_DI("tokenEvent: onFillFromOfFuncCall(%s, runExpr[%s])", me.getType().
                getName().c_str(), to.getName().c_str());

        to.setMe(me);
        return &to;
    }

    node* me::onAssign(node& lhs, node& rhs) {
        WRD_DI("tokenEvent: onAssign(%s, %s)", lhs.getType().getName().c_str(),
                rhs.getType().getName().c_str());
        return new assignExpr(lhs, rhs);
    }

    expr* me::onDefAssign(const std::string& name, node& rhs) {
        WRD_DI("tokenEvent: onDefAssign(%s, %s)", name.c_str(), rhs.getType().getName().c_str());
        return new defAssignExpr(name, rhs);
    }

    asExpr* me::onAs(const node& me, const node& as) {
        WRD_DI("tokenEvent: onAs(%s, %s)", me.getType().getName().c_str(), as.getType().getName().c_str());

        return new asExpr(me, as);
    }

    addExpr* me::onAdd(const node& lhs, const node& rhs) {
        WRD_DI("tokenEvent: onAdd(%s, %s)", lhs.getType().getName().c_str(), rhs.getType().getName()
                .c_str());

        return new addExpr(lhs, rhs);
    }



    me::loweventer() { rel(); }

    tstr<slot>& me::getPack() { return _slot; }
    tstr<obj>& me::getSubPack() { return _subpack; } // TODO: can I remove subpack variable?
    tstr<errReport>& me::getReport() { return _report; }
    tokenDispatcher& me::getDispatcher() { return _dispatcher; }
    std::vector<wcnt>& me::getIndents() { return _indents; }
    const area& me::getArea() const {
        static area dummy {{0, 0}, {0, 1}};

        return _srcArea ? *_srcArea : dummy;
    }
    wbool me::isInit() const { return _mode; }

    void me::rel() {
        _report.bind(dummyErrReport::singletone);
        _slot.rel();
        _nameMap.clear();
        _states.clear();
        _states.push_back(0); // 0 for default state
        prepareParse();
    }

    void me::prepareParse() {
        _mode = nullptr;
        _subpack.rel();
        _isIgnoreWhitespace = false;
        _dispatcher.rel();
        _indents.clear();
        _srcArea = nullptr;
    }
}
