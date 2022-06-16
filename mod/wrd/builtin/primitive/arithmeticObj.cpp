#include "arithmeticObj.hpp"

namespace wrd {

    WRD_DEF_ME(arithmeticObj)

#define _X(FUNC) const wtype& reduced = getType().reduce(rhs); \
        const arithmeticObj& winner = getType() == reduced ? *this : rhs; \
        const arithmeticObj& loser = getType() == reduced ? rhs : *this;

    tstr<arithmeticObj> me::add(const arithmeticObj& rhs) {
        _X(_add)
        return winner._add(loser);
    }
    tstr<arithmeticObj> me::sub(const arithmeticObj& rhs) {
        _X(_sub)
        return winner._sub(loser);
    }
    tstr<arithmeticObj> me::mul(const arithmeticObj& rhs) {
        _X(_mul)
        return winner._mul(loser);
    }
    tstr<arithmeticObj> me::div(const arithmeticObj& rhs) {
        _X(_div)
        return winner._div(loser);
    }
    tstr<arithmeticObj> me::mod(const arithmeticObj& rhs) {
        _X(_mod)
        return winner._mod(loser);
    }

#undef _X
}
