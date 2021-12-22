#pragma once

#include "../../common.hpp"
#include <list>

namespace wrd {

    class tokenDispatcher {
    public:
        void add(wint newToken) {
            _toks.push_back(newToken);
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

    private:
        std::list<wint> _toks;
    };
}
