#pragma once

#include "../builtin/container/native/tnarr.inl"

namespace wrd {

    class node;

    class scope : public narr {
        WRD(CLASS(scope, narr))

    public:
        wbool add(widx n, const node& new1) override;
    };
}
