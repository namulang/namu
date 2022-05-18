#pragma once

#include <vector>
#include <functional>
#include "../../ast/node.hpp"
#include "tokenDispatcher.hpp"
#include "bison/tokenScan.hpp"
#include "../errReport.hpp"
#include "../../ast/pack.hpp"
#include "../../ast/params.hpp"

namespace wrd {

    class expr;
    class mgdFunc;
    class blockExpr;
    class returnExpr;
    class runExpr;
    class loweventer : public tokenScan {
        WRD(CLASS(loweventer, tokenScan))
        friend class tokenScanModable;

    public:
        loweventer() { rel(); }

    public:
        tstr<pack>& getPack() { return _pack; }
        str& getSubPack() { return _subpack; } // TODO: can I remove subpack variable?
        tstr<errReport>& getReport() { return _report; }
        tokenDispatcher& getDispatcher() { return _dispatcher; }
        std::vector<wcnt>& getIndents() { return _indents; }
        const area& getArea() const {
            static area dummy {{0, 0}, {0, 1}};

            return _srcArea ? *_srcArea : dummy;
        }
        wbool isInit() const { return _mode; }

        template <typename T>
        void setScan() {
            WRD_DI("change scanmode(%s -> %s)", !_mode ? "<null>" : _mode->getType().getName().c_str(),
                    T::_instance->getType().getName().c_str());
            _mode = T::_instance;
        }

        void rel() {
            _report.bind(dummyErrReport::singletone);
            _pack.rel();
            _nameMap.clear();
            prepareParse();
        }

        void prepareParse() {
            _mode = nullptr;
            _subpack.rel();
            _isIgnoreWhitespace = false;
            _dispatcher.rel();
            _indents.clear();
            _srcArea = nullptr;
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
        template <typename... Args> void onSrcErr(Args... args) { _onRes(err::newErr(getArea(), args...)); }
        template <typename... Args> void onSrcWarn(Args... args) { _onRes(err::newWarn(getArea(), args...)); }
        template <typename... Args> void onSrcInfo(Args... args) { _onRes(err::newInfo(getArea(), args...)); }

        //  operator:
        //      dot:
        narr* onDotName(const std::string& name);
        narr* onDotName(narr& names, const std::string& name);
        node* onGet(const std::string& name);
        node* onGet(const std::string& name, const narr& args);
        node* onGet(node& from, const std::string& name, const narr& args);

        //  keyword:
        node* onPack(const narr& dotname);
        node* onPack();
        blockExpr* onBlock();
        blockExpr* onBlock(blockExpr& blk, node& exp);
        scope* onDefBlock();
        scope* onDefBlock(scope& blk, node& exp);

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
        expr* onDefVar(const std::string& name, const node& origin);
        //      file:
        void onCompilationUnit(node& subpack, scope& blk);
        //      return:
        returnExpr* onReturn();
        returnExpr* onReturn(node& exp);
        //      run:
        runExpr* onFillFromOfFuncCall(const node& me, runExpr& to);
        runExpr* onRunExpr(const std::string& name, const narr& args);

    private:
        wint _onScan(YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner);
        void _onRes(err* new1);
        params _convertParams(const narr& exprs);
        void _onPushName(const std::string& name, node& n);
        std::string _onPopName(node& n);

    private:
        tokenScan* _mode;
        wbool _isIgnoreWhitespace;
        tokenDispatcher _dispatcher;
        std::vector<wcnt> _indents;
        tstr<errReport> _report;
        tstr<pack> _pack;
        str _subpack;
        area* _srcArea;
        std::map<node*, std::string> _nameMap;
    };
}
