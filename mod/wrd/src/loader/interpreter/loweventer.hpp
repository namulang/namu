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
        loweventer(): _mode(nullptr) {
            _indents.push_back(0);
        }

    public:
        str& getRoot() { return _root; }
        tokenDispatcher& getDispatcher() { return _dispatcher; }
        std::vector<wcnt> getIndents() { return _indents; }
        wbool isInit() const { return _mode; }

        template <typename T>
        void setScan() {
            WRD_DI("change scanmode(%s -> %s)", !_mode ? "" : _mode->getType().getName().c_str(),
                    T::_instance->getType().getName().c_str());
            _mode = T::_instance;
        }

    public:
        // events:
        wint onScan(loweventer& eventer, YYSTYPE* yylval, YYLTYPE* yylloc, yyscan_t scanner) override;

    private:
        tokenScan* _mode;
        str _root;
        tokenDispatcher _dispatcher;
        std::vector<wcnt> _indents;
    };
}
