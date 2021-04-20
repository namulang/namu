#include "iteration.hpp"
#include "../../containable.hpp"

namespace wrd {

    WRD_DEF_ME(iteration)

    wbool me::isFrom(const ncontainer& rhs) const {
        return &getContainer() == &rhs;
    }

    wbool me::_onSame(const typeProvidable& rhs) const {
        const me& cast = (const me&) rhs;
        return isFrom(cast.getContainer());
    }
}
