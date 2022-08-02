#pragma once

#include "../../common.hpp"

namespace namu {

    class _wout asable {
    public:
        virtual wbool is(const type& from, const type& to) const = 0;
        virtual str as(const node& from, const type& to) const = 0;
    };

    typedef std::vector<asable*> asables;
}
