#pragma once

#include "Iterable.hpp"
#include "../Containable.hpp"

namespace wrd {

    class Iteration : public Instance, public Iterable {
        WRD_CLASS(Iteration)
        friend class Iter;

    public:
        Iteration(const Containable& own): _own(const_cast<Containable&>(own)) {}

        virtual wbool operator==(const Iteration& rhs) const {
            return isFrom(rhs._own);
        }

        wbool isFrom(const Containable& rhs) const override {
            return &_own == &rhs;
        }

    protected:
        Containable& _own;
    };

}
