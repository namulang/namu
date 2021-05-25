#include "sobj.hpp"
#include "nullSobj.hpp"

namespace wrd {

    WRD_DEF_ME(sobj)

    me& me::sub(const std::string& name) {
        tstr<me>& ret = _subs[name];
        if(!ret)
                return nullSobj::get();

        return *ret;
    }
}
