#pragma once

#include "../../common.hpp"
#include <list>

namespace wrd {

    class _wout tokenDispatcher {
    public:
        void add(wint newToken);
        void addFront(wint newToken);
        wbool pop(wint& output);

        wcnt len() const;

        void rel();

    private:
        std::list<wint> _toks;
    };
}
