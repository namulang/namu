#include "cast.hpp"
#include "wtype.hpp"

namespace wrd {

    WRD_DEF_ME(cast)

    wbool me::is(const wtype& to) const {
        return getType() == to;
    }
}
