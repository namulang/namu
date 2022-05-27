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
        pack* pak = &getPack().get();

        // pack syntax rule #1:
        //  if there is no specified name of pack, I create an one.
        std::string firstName = dotname[0].cast<std::string>();
        if(nul(pak))
            getPack().bind(pak = new pack(manifest(firstName), packLoadings()));

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
                e->subs().add(name, sub = new mgdObj());
            e = sub;
        }

        _subpack.bind(e);
        return e;
    }

    node* me::onPack() {
        WRD_DI("tokenEvent: onPack()");

        onWarn(errCode::NO_PACK);

        pack* newPack = &_pack.get();
        if(!_pack)
            _pack.bind(newPack = new pack(manifest(), packLoadings()));

        const std::string& name = _pack->getManifest().name;
        if(name != manifest::DEFAULT_NAME)
            return onErr(errCode::PACK_NOT_MATCH, manifest::DEFAULT_NAME, name.c_str()), newPack;

        _subpack.bind(newPack); // this is a default pack containing name as '{default}'.
        return newPack;
    }

    blockExpr* me::onBlock() {
        WRD_DI("tokenEvent: onBlock()");
        return new blockExpr();
    }

    blockExpr* me::onBlock(blockExpr& blk, node& candidate) {
        WRD_DI("tokenEvent: onBlock()");
        if(nul(blk))
            return onSrcErr(errCode::IS_NULL, "blk"), onBlock();
        expr* e = &candidate.cast<expr>();
        if(nul(e))
            e = new literalExpr(candidate);

        blk.getStmts().add(e);
        WRD_DI("tokenEvent: onBlock().len=%d", blk.getStmts().len());
        return &blk;
    }

    scope* me::onDefBlock() {
        WRD_DI("tokenEvent: onDefBlock()");
        return new scope();
    }

    scope* me::onDefBlock(scope& s, node& candidate) {
        WRD_DI("tokenEvent: onDefBlock(candidate=%s)", candidate.getType().getName().c_str());
        if(nul(s))
            return onSrcErr(errCode::IS_NULL, "s"), onDefBlock();
        expr* e = &candidate.cast<expr>();
        if(nul(e))
            return onSrcErr(errCode::PARAM_HAS_VAL, candidate.getType().getName().c_str()), onDefBlock();

        defVarExpr& defVar = e->cast<defVarExpr>();
        if(!nul(defVar)) {
            s.add(defVar.getParam().getName(), *defVar.getParam().getOrigin());
            return &s;
        }

        s.add(_onPopName(*e), e);
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

    void me::onCompilationUnit(node& subpack, scope& arr) {
        WRD_DI("tokenEvent: onCompilationUnit(%x, arr[%x])", &subpack, &arr);
        if(nul(subpack)) {
            onErr(errCode::NO_PACK_TRAY);
            return;
        }

        bicontainable& con = subpack.subs();
        for(auto e=arr.begin(); e ;++e)
            con.add(e.getKey(), *e);
    }

    returnExpr* me::onReturn() {
        WRD_DI("tokenEvent: onReturn()");

        return new returnExpr();
    }
    returnExpr* me::onReturn(node& exp) {
        WRD_DI("tokenEvent: onReturn(%s)", exp.getType().getName().c_str());

        return new returnExpr(exp);
    }

    narr* me::onDotName(const std::string& name) {
        narr* ret = new narr();
        ret->add(new wStr(name));
        return ret;
    }
    narr* me::onDotName(narr& names, const std::string& name) {
        names.add(new wStr(name));
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
}
