#include "arithmeticObj.hpp"

namespace namu {

    NAMU_DEF_ME(arithmeticObj)

#define _X(FUNC) \
    tstr<arithmeticObj> me::FUNC(const arithmeticObj& rhs) { \
        const ntype& deduced = getType().deduce(rhs); \
        nbool normalOrder = getType() == deduced; \
        const arithmeticObj& winner = getType() == deduced ? *this : rhs; \
        const arithmeticObj& loser = getType() == deduced ? rhs : *this; \
        return winner._ ## FUNC(loser, !normalOrder); \
    }

    NAMU_EACH(_X, add, sub, mul, div, mod)

#undef _X
}
