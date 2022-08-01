#include "nullSobj.hpp"

namespace wrd {

    WRD_DEF_ME(nullSobj)

    me::nullSobj(): super() {}

    const std::string& me::asStr() const {
        static std::string inner = "";
        return inner;
    }

    wchar me::asChar() const {
        return '\0';
    }

    wint me::asInt() const {
        return 0;
    }

    wbool me::asBool() const {
        return false;
    }

    const type& me::getType() const {
        return ttype<me>::get();
    }

    wbool me::isExist() const {
        return false;
    }

    me& me::get() {
        static me inner;
        return inner;
    }
}
