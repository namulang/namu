#pragma once

#include <vector>
#include <functional>
#include "../../ast/node.hpp"
#include "tokenDispatcher.hpp"

namespace wrd {

    class loweventer : public typeProvidable, public clonable {
        WRD(CLASS(loweventer))

    public:
        void onUpdate(wcnt newCol) {
        }

        wint onScanToken(std::function<wint()> originScanner);

    public:
        str& getRoot() { return _root; }

    private:
        void _onIndent(int newlv) {
        }

        void _onDedent(int newlv) {
        }

    public:
        str _root;
        tokenDispatcher _dispatcher;
        std::vector<wcnt> _indents;
    };
}
