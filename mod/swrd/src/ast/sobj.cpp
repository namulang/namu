#include "sobj.hpp"
#include "nullSobj.hpp"

namespace wrd {

    WRD_DEF_ME(sobj)

    me& me::sub(const std::string& name) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-undefined-compare"
        if (this == nullptr)
            return nulOf<me>();
#pragma clang diagnostic pop
        tstr<me>& ret = _subs[name];
        if(!ret)
                return nullSobj::get();

        return *ret;
    }
}
