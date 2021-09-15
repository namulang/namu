#include "iteration.hpp"
#include "../../containable.hpp"

namespace wrd {

    WRD_DEF_ME(iteration)

    wbool me::isFrom(const ncontainer& rhs) const {
        return &getContainer() == &rhs;
    }
}
