#pragma once

#include <vector>
#include <functional>
#include "../../ast/node.hpp"
#include "tokenDispatcher.hpp"
#include "bison/tokenScan.hpp"
#include "../errReport.hpp"
#include "../../ast/pack.hpp"

namespace wrd {

    class blockExpr;
    class expr;
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
        }

    public:
        // events:
        //  scan:
        using super::onScan;
        wint onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner, wbool& isBypass) override;
        wint onEndOfFile(const area& loc);
        wint onIndent(wcnt col, wint tok);
        wint onDedent(wcnt col, wint tok, const area& loc);
        wint onIgnoreIndent(wint tok);
        void onNewLine();
        wchar onScanUnexpected(const area& src, const wchar* token);
        void onEndParse(const point& pt);

        //  err:
        void onErr(const err* new1);
        //  keyword:
        str onPack(const area& src, const narr& dotname);
        str onPack();
        blockExpr* onBlock();
        blockExpr* onBlock(const area& src, blockExpr& blk, expr& exp);

    private:
        wint _onScan(YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner);
        str _onFindSubPack(node* subpack) {
            _subpack.bind(subpack);
            return _subpack;
        }

    private:
        tokenScan* _mode;
        wbool _isIgnoreWhitespace;
        tokenDispatcher _dispatcher;
        std::vector<wcnt> _indents;
        tstr<errReport> _report;
        tstr<pack> _pack;
        str _subpack;
    };
}
