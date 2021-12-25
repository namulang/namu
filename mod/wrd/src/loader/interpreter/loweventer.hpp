#pragma once

#include <vector>
#include <functional>
#include "../../ast/node.hpp"
#include "tokenDispatcher.hpp"
#include "bison/tokenScan.hpp"

namespace wrd {

    class loweventer : public tokenScan {
        WRD(CLASS(loweventer, tokenScan))
        friend class tokenScanModable;

    public:
        loweventer(): _mode(nullptr) {}

    public:
        str& getRoot() { return _root; }
        tokenDispatcher& getDispatcher() { return _dispatcher; }
        std::vector<wcnt>& getIndents() { return _indents; }
        wbool isInit() const { return _mode; }

        template <typename T>
        void setScan() {
            WRD_DI("change scanmode(%s -> %s)", !_mode ? "<null>" : _mode->getType().getName().c_str(),
                    T::_instance->getType().getName().c_str());
            _mode = T::_instance;
        }

    public:
        // events:
        using super::onScan;
        wint onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner, wbool& isBypass) override;
        wint onEndOfFile();
        wint onIndent(wcnt col, wint tok);
        wint onDedent(wcnt col, wint tok);
        void onNewLine();

    private:
        tokenScan* _mode;
        str _root;
        tokenDispatcher _dispatcher;
        std::vector<wcnt> _indents;
    };
}
