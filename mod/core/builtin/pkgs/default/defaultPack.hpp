#pragma once

#include "../../../ast/baseObj.hpp"

namespace namu {
    class _nout defaultPack : public baseObj {
        NAMU(CLASS(defaultPack, baseObj))

    public:
        using super::subs;
        nbicontainer& subs() override;

        const baseObj& getOrigin() const override;
    };
}
