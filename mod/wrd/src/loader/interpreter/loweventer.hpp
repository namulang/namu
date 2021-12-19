#pragma once

#include <vector>
#include <functional>
#include "../../ast/node.hpp"
#include "tokenDispatcher.hpp"
#include "bison/tokenScanable.hpp"

namespace wrd {

    typedef union YYSTYPE YYSTYPE;
    typedef struct lloc YYLTYPE;
    typedef void* yyscan_t;

    class loweventer : public typeProvidable, public clonable, public tokenScanable {
        WRD(CLASS(loweventer))
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
            _mode = T::_instance;
        }

    public:
        // events:
        wint onScan(loweventer& eventer, YYSTYPE* yylval, YYLTYPE* yylloc, yyscan_t scanner) override;

    private:
        tokenScanable* _mode;
        str _root;
        tokenDispatcher _dispatcher;
        std::vector<wcnt> _indents;
    };
}
