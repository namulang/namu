#pragma once

#include <vector>
#include <functional>
#include "../../ast/node.hpp"
#include "tokenDispatcher.hpp"

namespace wrd {

    class loweventer;
    typedef std::function<wint()> tokenScan;
    typedef std::function<wint(loweventer&, tokenScan)> tokenScanMode;

    class loweventer : public typeProvidable, public clonable {
        WRD(CLASS(loweventer))
        friend class tokenScanModable;

    public:
        loweventer();

    public:
        void onScanIndent(wcnt newCol) {
            int prevlv = _indents.size() ? _indents.back() : 0;
        }

        wint onScanToken(tokenScan originScanner) {
            return _mode(*this, originScanner);
        }

    public:
        str& getRoot() { return _root; }
        tokenDispatcher& getDispatcher() { return _dispatcher; }
        void setTokenScanMode(tokenScanMode new1) {
            _mode = new1;
        }
        std::vector<wcnt>& getIndents() { return _indents; }

    private:
        void _onIndent(int newlv) {
        }

        void _onDedent(int newlv) {
        }

    private:
        str _root;
        tokenDispatcher _dispatcher;
        tokenScanMode _mode;
        std::vector<wcnt> _indents;
    };
}
