#include "Iteration.hpp"
#include "../Containable.hpp"

namespace wrd {

    WRD_DEF_THIS(Iteration)

    wbool This::isFrom(const NContainer& rhs) const {
        return &getContainer() == &rhs;
    }

    wbool This::_onSame(const TypeProvidable& rhs) const {
        const This& cast = (const This&) rhs;
        return isFrom(cast.getContainer());
    }
}
