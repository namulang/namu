#include "loweventer.hpp"
#include "bison/lowparser.hpp"
#include "../../ast.hpp"
#include "../../ast/mgd/mgdFunc.hpp"
#include "../../builtin/primitive.hpp"
#include "../../frame/thread.hpp"
#include "../../ast/genericObj.hpp"
#include "../../type/mgdType.hpp"

namespace namu {

    using std::string;
    NAMU_DEF_ME(loweventer)

    namespace {
        string merge(const narr& dotname) {
            string ret;
            for(auto& e : dotname)
                ret += e.cast<std::string>();
            return ret;
        }
    }

    nint me::_onScan(YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner) {
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

    nint me::onScan(loweventer& ev, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner, nbool& isBypass) {
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

    nint me::onEndOfFile() {
        NAMU_DI("tokenEvent: onEndOfFile() indents.size()=%d", _indents.size());
        if(_indents.size() <= 1)
            _dispatcher.add(SCAN_MODE_END);
        else
            _dispatcher.addFront(onDedent(_indents.front(), SCAN_MODE_END));

        NAMU_DI("tokenEvent: onEndOfFile: finalize by adding 'NEWLINE', then dispatch end-of-file.");
        return NEWLINE;
    }

    nint me::onIndent(ncnt col, nint tok) {
        NAMU_DI("tokenEvent: onIndent(col: %d, tok: %d) indents.size()=%d", col, tok, _indents.size());
        _indents.push_back(col);
        _dispatcher.add(tok);
        return INDENT;
    }

    nint me::onDedent(ncnt col, nint tok) {
        NAMU_DI("tokenEvent: onDedent(col: %d, tok: %d) indents.size()=%d", col, tok, _indents.size());

        _indents.pop_back();
        nint now = _indents.back();
        if(now < col)
            onSrcWarn(errCode::WRONG_INDENT_LV, col, now, now);

        while(_indents.back() > col) {
            NAMU_DI("tokenEvent: onDedent: indentlv become %d -> %d", _indents.back(), _indents[_indents.size()-2]);
            _indents.pop_back();
            _dispatcher.add(DEDENT);
        }

        _dispatcher.add(tok);
        return DEDENT;
    }

    void me::onNewLine() {
        NAMU_DI("tokenEvent: onNewLine: _isIgnoreWhitespace=%s, _indents.size()=%d",
            _isIgnoreWhitespace ? "true" : "false", _indents.size());
        if(!_isIgnoreWhitespace && _indents.size() >= 1)
            _dispatcher.add(SCAN_MODE_INDENT);
    }

    nchar me::onScanUnexpected(const nchar* token) {
        onSrcErr(errCode::UNEXPECTED_TOK, token);
        return token[0];
    }

    nint me::onIgnoreIndent(nint tok) {
        NAMU_DI("tokenEvent: onIgnoreIndent(%d)", tok);
        _dispatcher.add(SCAN_MODE_INDENT_IGNORE);
        return tok;
    }

    void me::onEndParse() {
        area& area = *_srcArea;
#if NAMU_IS_DBG
        const point& pt = area.start;
        NAMU_DI("tokenEvent: onEndParse(%d,%d)", pt.row, pt.col);
#endif
        area.rel();
    }

    obj* me::onPack(const narr& dotname) {
        NAMU_DI("tokenEvent: onPack(%s)", merge(dotname).c_str());

        // pack syntax rule #1:
        //  if there is no specified name of pack, I create an one.
        std::string firstName = dotname[0].cast<std::string>();
        if(!_slot)
            _slot.bind(new slot(manifest(firstName)));
        obj* e = &_slot->getPack();

        const std::string& realName = _slot->getManifest().name;
        if(realName != firstName)
            return onErr(errCode::PACK_NOT_MATCH, firstName.c_str(), realName.c_str()), e;

        // pack syntax rule #2:
        //  middle name automatically created if not exist.
        //  on interpreting 'mypack' pack, user may uses 'pack' keyword with dotted-name.
        //  for instance,
        //      'pack mypack.component.ui'
        //  in this scenario, mypack instance should be created before. and component sub
        //  pack object can be created in this parsing keyword.
        for(int n=1; n < dotname.len(); n++) {
            const std::string& name = dotname[n].cast<std::string>();
            obj* sub = &e->sub<obj>(name);
            if(nul(sub))
                e->subs().add(name, sub = new obj(new mgdType(name)));
            e = sub;
        }

        _subpack.bind(e);
        return e;
    }

    obj* me::onPack() {
        NAMU_DI("tokenEvent: onPack()");

        onWarn(errCode::NO_PACK);

        slot* newSlot = &_slot.get();
        if(nul(newSlot))
            _slot.bind(newSlot = new slot(manifest()));

        const std::string& name = _slot->getManifest().name;
        if(name != manifest::DEFAULT_NAME)
            return onErr(errCode::PACK_NOT_MATCH, manifest::DEFAULT_NAME, name.c_str()), &newSlot->getPack();

        _subpack.bind(newSlot->getPack()); // this is a default pack containing name as '{default}'.
        return &_subpack.get();
    }

    blockExpr* me::onBlock() {
        NAMU_DI("tokenEvent: onBlock()");
        return new blockExpr();
    }

    blockExpr* me::onBlock(blockExpr& blk, node& stmt) {
        NAMU_DI("tokenEvent: onBlock()");
        if(nul(blk))
            return onSrcErr(errCode::IS_NULL, "blk"), onBlock();

        blk.getStmts().add(stmt);
        NAMU_DI("tokenEvent: onBlock().len=%d", blk.getStmts().len());
        return &blk;
    }

    defBlock* me::onDefBlock() {
        NAMU_DI("tokenEvent: onDefBlock()");
        return new defBlock();
    }

    defBlock* me::onDefBlock(defBlock& s, node& candidate) {
        NAMU_DI("tokenEvent: onDefBlock(candidate=%s)", candidate.getType().getName().c_str());
        if(nul(s))
            return onSrcErr(errCode::IS_NULL, "s"), onDefBlock();

        defVarExpr& defVar = candidate.cast<defVarExpr>();
        if(!nul(defVar)) {
            s.asScope->add(defVar.getName(), defVar.getOrigin());
            return &s;
        }
        defAssignExpr& defAssign = candidate.cast<defAssignExpr>();
        if(!nul(defAssign)) {
            defAssign.setTo(*new getExpr("me"));
            defAssign.setOnDefBlock(true);
            s.asPreCtor->add(defAssign);
            return &s;
        }

        s.asScope->add(_onPopName(candidate), &candidate);
        return &s;
    }

    node* me::onDefVar(const std::string& name, const node& origin) {
        NAMU_DI("tokenEvent: onDefVar(%s, %s)", origin.getType().getName().c_str(), name.c_str());

        return new defVarExpr(name, origin);
    }

    node* me::onDefArray(const narr& items) {
        NAMU_DI("tokenEvent: onDefArray(items.len[%d])", items.len());
        return new defArrayExpr(items);
    }

    node* me::onDefSeq(const node& start, const node& end) {
        NAMU_DI("tokenEvent: onDefSeq()");

        return new defSeqExpr(start, end);
    }

    void me::onSrcArea(area& area) {
        _srcArea = &area;
    }

    void me::_onRes(err* new1) {
        new1->log();
        _report->add(new1);
    }

    params me::_convertParams(const narr& ps) {
        params ret;
        for(auto& p : ps) {
            tstr<defVarExpr> defVar(p.cast<defVarExpr>());
            if(!defVar) return onSrcErr(errCode::PARAM_HAS_VAL), ret;

            ret.add(new param(defVar->getName(), defVar->getOrigin()));
        }

        return ret;
    }

    mgdFunc* me::onFunc(const std::string& name, const narr& exprs, const node& evalObj, const blockExpr& blk) {
        const ntype& evalType = evalObj.getType();
        NAMU_DI("tokenEvent: onFunc: %s(...[%x]) %s: blk.len()=%d", name.c_str(), &exprs,
                evalType.getName().c_str(), blk.getStmts().len());

        mgdFunc* ret = new mgdFunc(_convertParams(exprs), evalObj, blk);
        _onPushName(name, *ret);
        return ret;
    }

    narr* me::onList() {
        narr* ret = new narr();
        NAMU_DI("tokenEvent: onList()=%x", ret);
        return ret;
    }
    narr* me::onList(node* newExpr) {
        narr* ret = new narr(*newExpr);
        NAMU_DI("tokenEvent: onList(%s[%x])=%x", newExpr->getType().getName().c_str(), newExpr, ret);
        return ret;
    }
    narr* me::onList(narr& list, node* newExpr) {
        NAMU_DI("tokenEvent: onList(list[%x], %s[%x])", &list, newExpr->getType().getName().c_str(), newExpr);
        list.add(newExpr);
        return &list;
    }

    args* me::onTypeNames(const node& param) {
        NAMU_DI("tokenEvent: onTypeNames(%s)", param.getType().getName().c_str());
        auto* ret = new args();
        ret->add(param);
        return ret;
    }
    args* me::onTypeNames(args& params, const node& param) {
        NAMU_DI("tokenEvent: onTypeNames(len[%d], %s)", params.len(), param.getType().getName().c_str());
        params.add(param);
        return &params;
    }

    obj* me::onDefObj(const std::string& name, defBlock& blk) {
        NAMU_DI("tokenEvent: onDefObj(%s, defBlock[%x])", name.c_str(), &blk);

        obj& ret = *new obj(new mgdType(name));
        _onInjectObjSubs(ret, blk);
        _onPushName(name, ret);
        return &ret;
    }

    std::vector<std::string> me::_extractParamTypeNames(const args& types) {
        std::vector<std::string> ret;
        for(const auto& a : types) {
            // all args should be getExpr instances.
            const getExpr& cast = a.cast<getExpr>();
            if(nul(cast))
                return onSrcErr(errCode::SHOULD_TYPE_PARAM_NAME, a.getType().getName().c_str()),
                       std::vector<std::string>();

            ret.push_back(cast.getSubName());
        }

        return ret;
    }

    node* me::onDefObjGeneric(const std::string& name, const args& typeParams, defBlock& blk) {
        NAMU_DI("tokenEvent: onDefObjGeneric(%s, type.len[%d], defBlock[%x]", name.c_str(),
                typeParams.len(), &blk);

        obj& org = *new obj(new mgdType(name));
        _onInjectObjSubs(org, blk);
        node* ret = new genericObj(org, _extractParamTypeNames(typeParams));
        _onPushName(name, *ret);
        return ret;
    }

    void me::onCompilationUnit(obj& subpack, defBlock& blk) {
        NAMU_DI("tokenEvent: onCompilationUnit(%x, defBlock[%x])", &subpack, &blk);
        if(nul(subpack)) {
            onErr(errCode::NO_PACK_TRAY);
            return;
        }

        _onInjectObjSubs(subpack, blk);
        int len = (blk.asPreCtor) ? blk.asPreCtor->len() : 0;
        // at this far, subpack must have at least 1 default ctor created just before:
        NAMU_DI("tokenEvent: onCompilationUnit: run preconstructor(%d lines)", len);
        subpack.run(baseObj::CTOR_NAME); // don't need argument. it's default ctor.
    }

    nbool me::_onInjectObjSubs(obj& it, defBlock& blk) {
        NAMU_DI("tokenEvent: _onInjectObjSubs(%s, defBlock[%x])", it.getType().getName().c_str(), &blk);
        if(nul(it)) return false;

        bicontainable& share = it.getShares().getContainer();
        bicontainable& own = it.getOwns();
        for(auto e=blk.asScope->begin(); e ;++e) {
            bicontainable& con = nul(e.getVal<func>()) ? own : share;
            con.add(e.getKey(), *e);
        }

        // link system slots:
        it.getShares().link(thread::get().getSlots());
        NAMU_DI("link system slots[%d]: len=%d", thread::get().getSlots().len(), it.subs().len());

        return _onInjectCtor(it, blk);
    }

    nbool me::_onInjectCtor(obj& it, defBlock& blk) {
        nbool hasCtor = !nul(it.sub(baseObj::CTOR_NAME));
        NAMU_DI("tokenEvent: _onInjectDefaultCtor(%s, has=%d)", it.getType().getName().c_str(), hasCtor);
        if(hasCtor) return false;

        // TODO: ctor need to call superclass's ctor.
        it.getShares().getContainer().add(baseObj::CTOR_NAME, *new defaultCtor(it.getOrigin()));

        // add preCtor:
        if(blk.asPreCtor && blk.asPreCtor->len()) {
            mgdFunc* preCtor = new mgdFunc(params(), new nVoid());
            preCtor->getBlock().getStmts().add(*blk.asPreCtor);
            it.subs().add(baseObj::PRECTOR_NAME, preCtor);
        }
        return true;
    }

    retExpr* me::onRet() {
        NAMU_DI("tokenEvent: onRet()");

        return new retExpr();
    }
    retExpr* me::onRet(node& exp) {
        NAMU_DI("tokenEvent: onRet(%s)", exp.getType().getName().c_str());

        return new retExpr(exp);
    }

    breakExpr* me::onBreak() {
        NAMU_DI("tokenEvent: onBreak()");

        return new breakExpr();
    }
    breakExpr* me::onBreak(node& exp) {
        NAMU_DI("tokenEvent: onBreak(%s)", exp.getType().getName().c_str());

        return new breakExpr(exp);
    }

    nextExpr* me::onNext() {
        NAMU_DI("tokenEvent: onNext()");

        return new nextExpr();
    }

    narr* me::onPackDotname(const std::string& name) {
        narr* ret = new narr();
        ret->add(new nStr(name));
        return ret;
    }
    narr* me::onPackDotname(narr& names, const std::string& name) {
        names.add(new nStr(name));
        return &names;
    }

    getExpr* me::onDotname(const getExpr& from, getExpr& name) {
        name.setMe(from);
        return &name;
    }
    getExpr* me::onDotname(const std::string& name) {
        return new getExpr(name);
    }

    node* me::onGet(const std::string& name) {
        NAMU_DI("tokenEvent: onGet(%s)", name.c_str());
        return new getExpr(name);
    }
    node* me::onGet(const std::string& name, const narr& args) {
        NAMU_DI("tokenEvent: onGet(%s, %d)", name.c_str(), args.len());
        return new getExpr(name, args);
    }
    node* me::onGet(node& from, const std::string& name) {
        NAMU_DI("tokenEvent: onGet(%s, %s)", from.getType().getName().c_str(), name.c_str());
        return new getExpr(from, name);
    }
    node* me::onGet(node& from, const std::string& name, const narr& args) {
        NAMU_DI("tokenEvent: onGet(%s, %s, %d)", from.getType().getName().c_str(), name.c_str(),
                args.len());
        return new getExpr(from, name, args);
    }

    node* me::onGetArray(node& elemType) {
        NAMU_DI("tokenEvent: onGetArray(%s)", elemType.getType().getName().c_str());
        return new arr(elemType);
    }

    node* me::onGetElem(const node& arr, const node& idx) {
        NAMU_DI("tokenEvent: onGetElem(%s, %s)", arr.getType().getName().c_str(),
                idx.getType().getName().c_str());

        return new runExpr(arr, *new getExpr(arr, "get"), args{narr{idx}});
    }

    node* me::onGetGeneric(const std::string& genericObjName, const args& typeParams) {
        NAMU_DI("tokenEvent: onGetGeneric(%s, params.len[%d])", genericObjName.c_str(), typeParams.len());
        return new getGenericExpr(genericObjName, typeParams);
    }

    void me::_onPushName(const std::string& name, node& n) {
        _nameMap[&n] = name;
    }

    std::string me::_onPopName(node& n) {
        std::string ret = _nameMap[&n];
        _nameMap.erase(&n);
        return ret;
    }

    runExpr* me::onRunExpr(const node& trg, const narr& a) {
        NAMU_DI("tokenEvent: onRunExpr(%s, narr[%d])", trg.getType().getName().c_str(), a.len());

        return new runExpr(nulOf<node>(), trg, *new args(a));
    }
    runExpr* me::onRunExpr(const node& trg, const args& a) {
        NAMU_DI("tokenEvent: onRunExpr(%s, args[%d])", trg.getType().getName().c_str(), a.len());

        return new runExpr(nulOf<node>(), trg, a);
    }

    // @param from  can be expr. so I need to evaluate it through 'as()'.
    runExpr* me::onFillFromOfFuncCall(const node& me, runExpr& to) {
        NAMU_DI("tokenEvent: onFillFromOfFuncCall(%s, runExpr[%x])", me.getType().getName().c_str(), &to);

        to.setMe(me);
        return &to;
    }

    node* me::onAssign(node& lhs, node& rhs) {
        NAMU_DI("tokenEvent: onAssign(%s, %s)", lhs.getType().getName().c_str(),
                rhs.getType().getName().c_str());
        return new assignExpr(lhs, rhs);
    }

    node* me::onDefAssign(const std::string& name, node& rhs) {
        NAMU_DI("tokenEvent: onDefAssign(%s, %s)", name.c_str(), rhs.getType().getName().c_str());

        return new defAssignExpr(name, rhs);
    }

    asExpr* me::onAs(const node& me, const node& as) {
        NAMU_DI("tokenEvent: onAs(%s, %s)", me.getType().getName().c_str(), as.getType().getName().c_str());

        return new asExpr(me, as);
    }

    FAOExpr* me::onUnaryMinus(const node& it) {
        NAMU_DI("tokenEvent: onUnaryMinus(%s)", it.getType().getName().c_str());

        return new FAOExpr(FAOExpr::MUL, it, *new nInt(-1));
    }

    node* me::onUnaryDoublePlus(node& it) {
        NAMU_DI("tokenEvent: onUnaryDoublePlus(%s)", it.getType().getName().c_str());

        return onAssign(it, *new FAOExpr(FAOExpr::ADD, it, *new nInt(1)));
    }

    node* me::onUnaryDoubleMinus(node& it) {
        NAMU_DI("tokenEvent: onUnaryDoubleMinus(%s)", it.getType().getName().c_str());

        return onAssign(it, *new FAOExpr(FAOExpr::SUB, it, *new nInt(1)));
    }

    FAOExpr* me::onUnaryNot(const node& it) {
        NAMU_DI("tokenEvent: onUnaryNot(%s)", it.getType().getName().c_str());

        return new FAOExpr(FAOExpr::EQ, it, *new nBool(false));
    }

    FAOExpr* me::onAdd(const node& lhs, const node& rhs) {
        NAMU_DI("tokenEvent: onAdd(%s, %s)", lhs.getType().getName().c_str(), rhs.getType().getName()
                .c_str());

        return new FAOExpr(FAOExpr::ADD, lhs, rhs);
    }

    FAOExpr* me::onSub(const node& lhs, const node& rhs) {
        NAMU_DI("tokenEvent: onSub(%s, %s)", lhs.getType().getName().c_str(), rhs.getType().getName()
                .c_str());

        return new FAOExpr(FAOExpr::SUB, lhs, rhs);
    }

    FAOExpr* me::onMul(const node& lhs, const node& rhs) {
        NAMU_DI("tokenEvent: onMul(%s, %s)", lhs.getType().getName().c_str(), rhs.getType().getName()
                .c_str());

        return new FAOExpr(FAOExpr::MUL, lhs, rhs);
    }

    FAOExpr* me::onDiv(const node& lhs, const node& rhs) {
        NAMU_DI("tokenEvent: onDiv(%s, %s)", lhs.getType().getName().c_str(), rhs.getType().getName()
                .c_str());

        return new FAOExpr(FAOExpr::DIV, lhs, rhs);
    }

    FAOExpr* me::onMod(const node& lhs, const node& rhs) {
        NAMU_DI("tokenEvent: onMod(%s, %s)", lhs.getType().getName().c_str(), rhs.getType().getName()
                .c_str());

        return new FAOExpr(FAOExpr::MOD, lhs, rhs);
    }

    FAOExpr* me::onGt(const node& lhs, const node& rhs) {
        NAMU_DI("tokenEvent: onGt(%s, %s)", lhs.getType().getName().c_str(), rhs.getType().getName()
                .c_str());

        return new FAOExpr(FAOExpr::GT, lhs, rhs);
    }

    FAOExpr* me::onLt(const node& lhs, const node& rhs) {
        NAMU_DI("tokenEvent: onLt(%s, %s)", lhs.getType().getName().c_str(), rhs.getType().getName()
                .c_str());

        return new FAOExpr(FAOExpr::LT, lhs, rhs);
    }

    FAOExpr* me::onGe(const node& lhs, const node& rhs) {
        NAMU_DI("tokenEvent: onGe(%s, %s)", lhs.getType().getName().c_str(), rhs.getType().getName()
                .c_str());

        return new FAOExpr(FAOExpr::GE, lhs, rhs);
    }

    FAOExpr* me::onLe(const node& lhs, const node& rhs) {
        NAMU_DI("tokenEvent: onLe(%s, %s)", lhs.getType().getName().c_str(), rhs.getType().getName()
                .c_str());

        return new FAOExpr(FAOExpr::LE, lhs, rhs);
    }

    FAOExpr* me::onEq(const node& lhs, const node& rhs) {
        NAMU_DI("tokenEvent: onEq(%s, %s)", lhs.getType().getName().c_str(), rhs.getType().getName()
                .c_str());

        return new FAOExpr(FAOExpr::EQ, lhs, rhs);
    }

    FAOExpr* me::onNe(const node& lhs, const node& rhs) {
        NAMU_DI("tokenEvent: onNe(%s, %s)", lhs.getType().getName().c_str(), rhs.getType().getName()
                .c_str());

        return new FAOExpr(FAOExpr::NE, lhs, rhs);
    }

    FAOExpr* me::onAnd(const node& lhs, const node& rhs) {
        NAMU_DI("tokenEvent: onAnd(%s, %s)", lhs.getType().getName().c_str(), rhs.getType().getName()
                .c_str());

        return new FAOExpr(FAOExpr::AND, lhs, rhs);
    }

    FAOExpr* me::onOr(const node& lhs, const node& rhs) {
        NAMU_DI("tokenEvent: onOr(%s, %s)", lhs.getType().getName().c_str(), rhs.getType().getName()
                .c_str());

        return new FAOExpr(FAOExpr::OR, lhs, rhs);
    }

    node* me::onFor(const std::string& iterName, const node& expr, const blockExpr& blk) {
        NAMU_DI("tokenEvent: onFor(%s, %s)", iterName.c_str(), expr.getType().getName().c_str());

        return new forExpr(iterName, expr, blk);
    }

    node* me::onWhile(const node& condition, const blockExpr& blk) {
        NAMU_DI("tokenEvent: onWhile(%s)", condition.getType().getName().c_str());

        return new whileExpr(condition, blk);
    }

    node* me::onAkaDefault(const getExpr& dotname, const std::string& newName) {
        NAMU_DI("tokenEvent: onAkaDefault(%s..., %s)", dotname.getSubName().c_str(), newName.c_str());

        return new defAssignExpr(newName, dotname);
    }

    ifExpr* me::onIf(const node& condition, const blockExpr& thenBlk) {
        NAMU_DI("tokenEvent: onIf(then)");

        ifExpr* ret = new ifExpr(condition, thenBlk);
        _outerIfStack.push_back(ret);

        return ret;
    }
    ifExpr* me::onElif(ifExpr& ifexpr, const node& elseIfCondition, const blockExpr& thenBlk) {
        NAMU_DI("tokenEvent: onElIf(ifexpr, condition, then)");
        ifExpr* ret = new ifExpr(elseIfCondition, thenBlk);

        ifexpr.setElseBlk(*new blockExpr(*ret));
        return ret;
    }
    ifExpr* me::onElse(ifExpr& ifexpr, const blockExpr& elseBlk) {
        NAMU_DI("tokenEvent: onElse(ifexpr, elseBlk)");

        ifexpr.setElseBlk(elseBlk);
        return onEndOfIf();
    }
    ifExpr* me::onEndOfIf() {
        ifExpr* ret = _outerIfStack.back();
        _outerIfStack.pop_back();
        return ret;
    }

    me::loweventer() { rel(); }

    tstr<slot>& me::getSlot() { return _slot; }
    tstr<obj>& me::getSubPack() { return _subpack; } // TODO: can I remove subpack variable?
    tstr<errReport>& me::getReport() { return _report; }
    tokenDispatcher& me::getDispatcher() { return _dispatcher; }
    std::vector<ncnt>& me::getIndents() { return _indents; }
    const area& me::getArea() const {
        static area dummy {{0, 0}, {0, 1}};

        return _srcArea ? *_srcArea : dummy;
    }
    nbool me::isInit() const { return _mode; }

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
        _outerIfStack.clear();
    }
}
