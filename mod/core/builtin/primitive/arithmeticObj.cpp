#include "arithmeticObj.hpp"

namespace namu {

    WRD_DEF_ME(arithmeticObj)

#define _X(FUNC) \
        const wtype& reduced = getType().reduce(rhs); \
        wbool normalOrder = getType() == reduced; \
        const arithmeticObj& winner = getType() == reduced ? *this : rhs; \
        const arithmeticObj& loser = getType() == reduced ? rhs : *this; \

    tstr<arithmeticObj> me::add(const arithmeticObj& rhs) {
        _X(_add)
        return winner._add(loser, !normalOrder);
    }
    tstr<arithmeticObj> me::sub(const arithmeticObj& rhs) {
        _X(_sub)
        return winner._sub(loser, !normalOrder);
    }
    tstr<arithmeticObj> me::mul(const arithmeticObj& rhs) {
        _X(_mul)
        return winner._mul(loser, !normalOrder);
    }
    tstr<arithmeticObj> me::div(const arithmeticObj& rhs) {
        _X(_div)
        return winner._div(loser, !normalOrder);
    }
    tstr<arithmeticObj> me::mod(const arithmeticObj& rhs) {
        _X(_mod)
        return winner._mod(loser, !normalOrder);
    }

#undef _X
}
