#pragma once

#include <vector>
#include <functional>
#include "../../ast/node.hpp"
#include "tokenDispatcher.hpp"
#include "bison/tokenScan.hpp"
#include "../errReport.hpp"
#include "../../ast/slot.hpp"
#include "../../ast/params.hpp"
#include "defBlock.hpp"

namespace namu {

    class expr;
    class mgdFunc;
    class blockExpr;
    class returnExpr;
    class runExpr;
    class asExpr;
    class addExpr;
    class FAOExpr;
    class getExpr;
    class _wout loweventer : public tokenScan {
        WRD(CLASS(loweventer, tokenScan))
        friend class tokenScanModable;

    public:
        loweventer();

    public:
        tstr<slot>& getSlot();
        tstr<obj>& getSubPack();
        tstr<errReport>& getReport();
        tokenDispatcher& getDispatcher();
        std::vector<wcnt>& getIndents();
        const area& getArea() const;
        wbool isInit() const;

        template <typename T>
        void setScan() {
            WRD_DI("change scanmode(%s -> %s)", !_mode ? "<null>" : _mode->getType().getName().c_str(),
                    T::_instance->getType().getName().c_str());
            _mode = T::_instance;
        }

        void rel();
        void prepareParse();

        int pushState(int newState) {
            WRD_I("push state %d -> %d", _states.back(), newState);
            _states.push_back(newState);
            return _states.back();
        }

        int popState() {
            int previous = _states.back();
            _states.pop_back();
            WRD_I("pop state %d <- %d", _states.back(), previous);
            return _states.back();
        }

    public:
        // events:
        //  scan:
        using super::onScan;
        wint onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner, wbool& isBypass) override;
        wint onEndOfFile();
        wint onIndent(wcnt col, wint tok);
        wint onDedent(wcnt col, wint tok);
        wint onIgnoreIndent(wint tok);
        void onNewLine();
        wchar onScanUnexpected(const wchar* token);
        void onEndParse();
        void onSrcArea(area& area);

        //  err:
        template <typename... Args> void onErr(Args... args) { _onRes(err::newErr(args...)); }
        template <typename... Args> void onWarn(Args... args) { _onRes(err::newWarn(args...)); }
        template <typename... Args> void onInfo(Args... args) { _onRes(err::newInfo(args...)); }
        template <typename... Args> void onSrcErr(Args... args) { _onRes(err::newErr(getArea().start, args...)); }
        template <typename... Args> void onSrcWarn(Args... args) { _onRes(err::newWarn(getArea().start, args...)); }
        template <typename... Args> void onSrcInfo(Args... args) { _onRes(err::newInfo(getArea().start, args...)); }

        //  operator:
        //      dot:
        getExpr* onDotname(const getExpr& names, getExpr& name);
        getExpr* onDotname(const std::string& name);
        narr* onPackDotname(const std::string& name);
        narr* onPackDotname(narr& names, const std::string& name);
        node* onGet(const std::string& name);
        node* onGet(const std::string& name, const narr& args);
        node* onGet(node& from, const std::string& name);
        node* onGet(node& from, const std::string& name, const narr& args);
        //      assign:
        node* onAssign(node& lhs, node& rhs);

        //  keyword:
        obj* onPack(const narr& dotname);
        obj* onPack();
        blockExpr* onBlock();
        blockExpr* onBlock(blockExpr& blk, node& exp);
        defBlock* onDefBlock();
        defBlock* onDefBlock(defBlock& blk, node& exp);
        //      aka:
        node* onAkaDefault(const getExpr& dotname, const std::string& newName);

        //  expr:
        //      func:
        mgdFunc* onFunc(const std::string& name, const narr& params, const node& evalType, const blockExpr& blk);
        //      list:
        narr* onList();
        narr* onList(node* newExpr);
        narr* onList(narr& list, node* newExpr);
        //      var:
        template <typename T, typename... Args>
        T* onPrimitive(Args... args) {
            WRD_DI("on%s(...)", ttype<T>::get().getName().c_str());
            return new T(args...);
        }
        node* onDefVar(const std::string& name, const node& origin);
        node* onDefAssign(const std::string& name, node& rhs);
        //      obj:
        obj* onDef(const std::string& name, defBlock& blk);
        //      file:
        void onCompilationUnit(obj& subpack, defBlock& blk);
        //      return:
        returnExpr* onReturn();
        returnExpr* onReturn(node& exp);
        //      run:
        runExpr* onFillFromOfFuncCall(const node& me, runExpr& to);
        runExpr* onRunExpr(const std::string& name, const narr& args);
        //      cast:
        asExpr* onAs(const node& me, const node& as);
        //      binary operation:
        FAOExpr* onAdd(const node& lhs, const node& rhs);
        FAOExpr* onSub(const node& lhs, const node& rhs);
        FAOExpr* onMul(const node& lhs, const node& rhs);
        FAOExpr* onDiv(const node& lhs, const node& rhs);
        FAOExpr* onMod(const node& lhs, const node& rhs);

    private:
        wint _onScan(YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner);
        void _onRes(err* new1);
        params _convertParams(const narr& exprs);
        void _onPushName(const std::string& name, node& n);
        std::string _onPopName(node& n);
        wbool _onPastePreCtors(obj& it, narr& blk);
        wbool _onInjectObjSubs(obj& it, defBlock& blk);
        wbool _onInjectCtor(obj& it, defBlock& blk);

    private:
        tokenScan* _mode;
        wbool _isIgnoreWhitespace;
        tokenDispatcher _dispatcher;
        std::vector<wcnt> _indents;
        tstr<errReport> _report;
        tstr<slot> _slot;
        tstr<obj> _subpack;
        area* _srcArea;
        std::vector<wint> _states;
        std::map<node*, std::string> _nameMap;
    };
}
