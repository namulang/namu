#pragma once

#include "iterable.hpp"
#include "../../ast/clonable.hpp"

namespace wrd {

    class iteration : public instance, public iterable, public clonable {
        WRD_INTERFACE(iteration, instance)
        friend class iterator;

    public:
        wbool isFrom(const ncontainer& rhs) const override;

    protected:
        wbool _onSame(const typeProvidable& rhs) const override;
    };
}
