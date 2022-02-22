#pragma once

#include <vector>
#include <functional>
#include "../../ast/node.hpp"
#include "tokenDispatcher.hpp"
#include "bison/tokenScan.hpp"
#include "../errReport.hpp"
#include "../../ast/pack.hpp"

namespace wrd {

    class expr;
    class mgdFunc;
    class blockExpr;
    class loweventer : public tokenScan {
        WRD(CLASS(loweventer, tokenScan))
        friend class tokenScanModable;

    public:
        loweventer() { rel(); }

    public:
        tstr<pack>& getPack() { return _pack; }
        str& getSubPack() { return _subpack; }
        tstr<errReport>& getReport() { return _report; }
        tokenDispatcher& getDispatcher() { return _dispatcher; }
        std::vector<wcnt>& getIndents() { return _indents; }
        const area& getArea() const { return *_srcArea; }
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

        //  keyword:
        str onPack(const narr& dotname);
        str onPack();
        node* onBlock();
        node* onBlock(blockExpr& blk, node& exp);

        //  defexpr:
        //      func:
        mgdFunc* onFunc(const std::string& name, const narr& params, const node& evalType, const blockExpr& blk);
        //      list:
        narr* onList();
        narr* onList(const expr* newExpr);
        narr* onList(narr& list, const expr* newExpr);
        //      var:
        template <typename T, typename... Args>
        node* onPrimitive(Args... args) {
            WRD_DI("on%s(...)", ttype<T>::get().getName().c_str());
            return new T(args...);
        }
        node* onDefVar(const wtype& t, const std::string& name);

    private:
        wint _onScan(YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner);
        str _onFindSubPack(node* subpack);
        void _onRes(err* new1);

    private:
        tokenScan* _mode;
        wbool _isIgnoreWhitespace;
        tokenDispatcher _dispatcher;
        std::vector<wcnt> _indents;
        tstr<errReport> _report;
        tstr<pack> _pack;
        str _subpack;
        area* _srcArea;
    };
}
