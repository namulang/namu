#pragma once

#include "../common.hpp"

namespace wrd {

    class Ref;
    class WType;
    struct As : public TypeProvidable {
        wbool is(const WType& to) const;

        virtual Ref as(const Node& it) const = 0;
    };

    typedef std::vector<As*> Ases;
}
