#include "As.hpp"
#include "WType.hpp"

namespace wrd {

    WRD_DEF_ME(As)

    wbool me::is(const WType& to) const {
        return getType() == to;
    }
}
