#pragma once

#include "../../common.hpp"

namespace namu {

    class _nout asable {
    public:
        virtual nbool is(const type& from, const type& to) const = 0;
        virtual str as(const node& from, const type& to) const = 0;
    };

    typedef std::vector<asable*> asables;
}
