#pragma once

#include "Iterable.hpp"
#include "../../ast/Clonable.hpp"

namespace wrd {

    class Containable;
    class Iteration : public Instance, public Iterable, public Clonable {
        WRD_INTERFACE(Iteration)
        friend class Iter;

    public:
        virtual wbool operator==(const Iteration& rhs) const {
            return isFrom(rhs.getContainer());
        }

        wbool isFrom(const Containable& rhs) const override {
            return &getContainer() == &rhs;
        }
    };
}
