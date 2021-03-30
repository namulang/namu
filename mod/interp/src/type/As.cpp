#include "As.hpp"
#include "WType.hpp"

namespace wrd {

    WRD_DEF_THIS(As)

    wbool This::is(const WType& to) const {
        return getType() == to;
    }
}
