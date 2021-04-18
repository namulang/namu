#pragma once

#include "../common.hpp"

namespace wrd {

    class ref;
    class wtype;
    struct cast : public typeProvidable {
        wbool is(const wtype& to) const;

        virtual ref as(const node& it) const = 0;
    };

    typedef std::vector<cast*> casts;
}
