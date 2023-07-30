#pragma once

#include "../builtin/container/native/tnarr.hpp"
#include "obj.hpp"

namespace namu {

    class _nout args : public narr {
        NAMU(CLASS(args, narr))

    public:
        args();
        args(const baseObj& me);
        args(const narr& rhs);
        args(const baseObj& me, const narr& rhs);

    public:
        const me& setMe(const node& me) const;
        node& getMe() const;

        clonable* deepClone() const override;

    private:
        mutable str _me;
    };
}
