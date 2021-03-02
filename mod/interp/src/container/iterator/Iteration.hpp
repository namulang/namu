#pragma once

#include "Iterable.hpp"
#include "../../ast/Clonable.hpp"

namespace wrd {

    class Containable;
    class Iteration : public Instance, public Iterable, public Clonable {
        WRD_INTERFACE(Iteration, Instance)
        friend class Iter;

    public:
        wbool isFrom(const Containable& rhs) const override {
            return &getContainer() == &rhs;
        }

    protected:
        wbool _onSame(const TypeProvidable& rhs) const override {
            const This& cast = (const This&) rhs;
            return isFrom(cast.getContainer());
        }
    };
}
