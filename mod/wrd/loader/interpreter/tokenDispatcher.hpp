#pragma once

#include "../../common.hpp"
#include <list>

namespace wrd {

    class _wout tokenDispatcher {
    public:
        void add(wint newToken) {
            _toks.push_back(newToken);
        }

        void addFront(wint newToken) {
            _toks.insert(_toks.begin(), newToken);
        }

        wbool pop(wint& output) {
            if(_toks.size() <= 0)
                return false;

            output = _toks.front();
            _toks.pop_front();
            return true;
        }

        wcnt len() const {
            return _toks.size();
        }

        void rel() {
            _toks.clear();
        }

    private:
        std::list<wint> _toks;
    };
}
