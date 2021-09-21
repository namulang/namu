#pragma once

#include "../builtin/container/native/tnarr.hpp"
#include "../builtin/container/native/tnchain.inl"

namespace wrd {

    class node;

    class scope : public narr {
        WRD(CLASS(scope, narr))

    public:
        wbool add(widx n, const node& new1) override;
    };

    typedef tnchain<node, scope> scopeChn;
}
