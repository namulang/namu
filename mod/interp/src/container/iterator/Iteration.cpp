#include "Iteration.hpp"
#include "../Containable.hpp"

namespace wrd {

    WRD_DEF_ME(Iteration)

    wbool me::isFrom(const NContainer& rhs) const {
        return &getContainer() == &rhs;
    }

    wbool me::_onSame(const TypeProvidable& rhs) const {
        const me& cast = (const me&) rhs;
        return isFrom(cast.getContainer());
    }
}
