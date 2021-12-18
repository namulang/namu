#pragma once

#include <vector>
#include <functional>
#include "../../ast/node.hpp"
#include "tokenDispatcher.hpp"
#include "bison/scanMode.hpp"

namespace wrd {

    class loweventer : public typeProvidable, public clonable {
        WRD(CLASS(loweventer))
        friend class tokenScanModable;

    public:
        loweventer(): _mode(nullptr) {}
        virtual ~loweventer();

    public:
        str& getRoot() { return _root; }
        tokenDispatcher& getDispatcher() { return _dispatcher; }
        std::vector<wcnt>& getIndents() { return _indents; }
        scanMode& getScanMode() const { return *_mode; }
        void setScanMode(scanMode* new1) {
            if(_mode)
                delete _mode;
            _mode = new1;
        }

    private:
        scanMode* _mode;
        str _root;
        tokenDispatcher _dispatcher;
        std::vector<wcnt> _indents;
    };
}
