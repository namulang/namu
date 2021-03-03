#pragma once

#include "Iterable.hpp"
#include "../../ast/Clonable.hpp"

namespace wrd {

    class Iteration : public Instance, public Iterable, public Clonable {
        WRD_INTERFACE(Iteration, Instance)
        friend class Iter;

    public:
        wbool isFrom(const NContainer& rhs) const override;

    protected:
        wbool _onSame(const TypeProvidable& rhs) const override;
    };
}
