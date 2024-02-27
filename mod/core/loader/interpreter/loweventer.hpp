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
#include "../../ast/exprs/exprMaker.hpp"
#include "../../ast/exprs/FBOExpr.hpp"

namespace namu {

    class expr;
    class mgdFunc;
    class blockExpr;
    class runExpr;
    class asExpr;
    class addExpr;
    class getExpr;
    class retExpr;
    class breakExpr;
    class nextExpr;
    class ifExpr;
    class FUOExpr;

    class _nout loweventer : public tokenScan {
        NAMU(CLASS(loweventer, tokenScan))
        friend class tokenScanModable;

    public:
        loweventer();

    public:
        tstr<slot>& getSlot();
        tstr<obj>& getSubPack();
        tstr<errReport>& getReport();
        tokenDispatcher& getDispatcher();
        std::vector<ncnt>& getIndents();
        const area& getArea() const;
        nbool isInit() const;

        template <typename T>
        void setScan() {
            NAMU_DI("change scanmode(%s -> %s)", !_mode ? "<null>" : _mode->getType().getName().c_str(),
                    T::_instance->getType().getName().c_str());
            _mode = T::_instance;
        }

        void rel();
        void prepareParse();

        int pushState(int newState);
        int popState();

        // events:
        //  scan:
        using super::onScan;
        nint onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner, nbool& isBypass) override;
        nint onEndOfFile();
        nint onIndent(ncnt col, nint tok);
        nint onDedent(ncnt col, nint tok);
        nint onIgnoreIndent(nint tok);
        void onNewLine();
        nchar onScanUnexpected(const nchar* token);
        void onEndParse();
        void onSrcArea(const area& area);

        //  err:
        template <typename... Args> void onErr(Args... args) { _onRes(err::newErr(args...)); }
        template <typename... Args> void onWarn(Args... args) { _onRes(err::newWarn(args...)); }
        template <typename... Args> void onInfo(Args... args) { _onRes(err::newInfo(args...)); }
        template <typename... Args> void onSrcErr(Args... args) { _onRes(err::newErr(getArea().start, args...)); }
        template <typename... Args> void onSrcWarn(Args... args) { _onRes(err::newWarn(getArea().start, args...)); }
        template <typename... Args> void onSrcInfo(Args... args) { _onRes(err::newInfo(getArea().start, args...)); }

        //  operator:
        //      dot:
        node* onGet(const std::string& name);
        node* onGet(const std::string& name, const narr& args);
        node* onGet(node& from, node& it);
        node* onCallAccess(node& it, narr& args);

        //      unary operation:
        FBOExpr* onUnaryMinus(const node& it);
        FBOExpr* onUnaryNot(const node& it);
        FUOExpr* onUnaryBitwiseNot(const node& it);
        node* onUnaryDoublePlus(node& it);
        node* onUnaryDoubleMinus(node& it);
        FUOExpr* onUnaryPostfixDoublePlus(const node& it);
        FUOExpr* onUnaryPostfixDoubleMinus(const node& it);
        //      binary operation:
        //          arithmetic:
        FBOExpr* onAdd(const node& lhs, const node& rhs);
        FBOExpr* onSub(const node& lhs, const node& rhs);
        FBOExpr* onMul(const node& lhs, const node& rhs);
        FBOExpr* onDiv(const node& lhs, const node& rhs);
        FBOExpr* onMod(const node& lhs, const node& rhs);
        //          bitwise:
        FBOExpr* onBitwiseAnd(const node& lhs, const node& rhs);
        FBOExpr* onBitwiseXor(const node& lhs, const node& rhs);
        FBOExpr* onBitwiseOr(const node& lhs, const node& rhs);
        FBOExpr* onLShift(const node& lhs, const node& rhs);
        FBOExpr* onRShift(const node& lhs, const node& rhs);
        //          assign:
        node* onAssign(node& lhs, node& rhs);
        node* onAddAssign(node& lhs, node& rhs);
        node* onSubAssign(node& lhs, node& rhs);
        node* onMulAssign(node& lhs, node& rhs);
        node* onDivAssign(node& lhs, node& rhs);
        node* onModAssign(node& lhs, node& rhs);
        //          logical:
        FBOExpr* onGt(const node& lhs, const node& rhs);
        FBOExpr* onGe(const node& lhs, const node& rhs);
        FBOExpr* onLt(const node& lhs, const node& rhs);
        FBOExpr* onLe(const node& lhs, const node& rhs);
        FBOExpr* onEq(const node& lhs, const node& rhs);
        FBOExpr* onNe(const node& lhs, const node& rhs);
        FBOExpr* onAnd(const node& lhs, const node& rhs);
        FBOExpr* onOr(const node& lhs, const node& rhs);

        //  generic:
        node* onGetGeneric(const std::string& genericObjName, const args& typeParams);
        node* onGetElem(const node& arr, const node& idx);
        //  container:
        node* onGetArray(node& elemType);

        //  keyword:
        obj* onPack(const node& path);
        obj* onPack();
        obj* onSubPack(obj& subpack);
        blockExpr* onBlock();
        blockExpr* onBlock(blockExpr& blk, node& exp);
        defBlock* onDefBlock();
        defBlock* onDefBlock(defBlock& blk, node& exp);
        node* onFor(const std::string& iterName, const node& expr, const blockExpr& blk);
        node* onWhile(const node& condition, const blockExpr& blk);

        //  expr:
        //      def:
        //          list:
        node* onParanthesisAsTuple(narr& tuple);
        narr* onTuple();
        narr* onTuple(node* newExpr);
        narr* onTuple(narr& list, node* newExpr);
        //          typenames:
        args* onTypeNames(const node& param);
        args* onTypeNames(args& params, const node& param);
        //          var:
        template <typename T, typename... Args>
        T* onPrimitive(Args... args) {
            NAMU_DI("on%s(...)", ttype<T>::get().getName().c_str());
            return new T(args...);
        }
        node* onDefVar(const std::string& name, const node& origin);
        node* onDefAssign(const std::string& name, node& rhs);
        //          obj:
        obj* onDefObj(const std::string& name, defBlock& blk);
        node* onDefObjGeneric(const std::string& name, const args& typeParams, defBlock& blk);
        //          container:
        node* onDefArray(const narr& items);
        node* onDefSeq(const node& start, const node& end);
        //          file:
        void onCompilationUnit(obj& subpack, defBlock& blk);
        //          func:
        mgdFunc* onFunc(const std::string& name, const narr& params, const node& evalType, const blockExpr& blk);
        // stmt:
        node* onDeclStmt(const narr& dotnames) {
            // TODO:
            return nullptr;
        }

        //      return:
        retExpr* onRet();
        retExpr* onRet(node& exp);
        breakExpr* onBreak();
        breakExpr* onBreak(node& exp);
        nextExpr* onNext();
        //      run:
        runExpr* onFillFromOfFuncCall(const node& me, runExpr& to);
        runExpr* onRunExpr(const node& type, const narr& a);
        runExpr* onRunExpr(const node& type, const args& a);
        //      cast:
        asExpr* onAs(const node& me, const node& as);
        //      if:
        ifExpr* onIf(const node& condition, const blockExpr& then);
        ifExpr* onIf(const node& condition, const blockExpr& then, const blockExpr& elseBlk);
        ifExpr* onIf(const node& condition, const blockExpr& then, const ifExpr& elseIf);

        void onParseErr(const std::string& msg, const nchar* symbolName);

    private:
        node* _onSetElem(runExpr& lhs, const node& rhs);
        node* _onAssignElem(FBOExpr::rule type, node& lhs, node& rhs);
        node* _onConvertAssignElem(runExpr& lhs, node& rhs);

        nint _onScan(YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner);
        void _onRes(err* new1);
        params _convertParams(const narr& exprs);

        void _onPushName(const std::string& name, node& n);
        std::string _onPopName(node& n);

        nbool _onInjectObjSubs(obj& it, defBlock& blk);
        nbool _onInjectCtor(obj& it, defBlock& blk);
        std::vector<std::string> _extractParamTypeNames(const args& types);
        const node& _onDefArrayType(const narr& items);
        std::vector<std::string> _toDotnames(const node& path);

    private:
        tokenScan* _mode;
        nbool _isIgnoreWhitespace;
        tokenDispatcher _dispatcher;
        std::vector<ncnt> _indents;
        tstr<errReport> _report;
        tstr<slot> _slot;
        tstr<obj> _subpack;
        area _srcArea;
        tstr<scope> _filescope;
        std::vector<nint> _states;
        std::map<node*, std::string> _nameMap;
        exprMaker _maker;
    };
}
