#include "../type/ttype.hpp"
#include "typeProvidable.hpp"

namespace wrd {

    WRD_DEF_ME(typeProvidable)

    wbool me::operator==(const me& rhs) const {
        if(nul(rhs)) return false;
        if(getType() != rhs.getType()) return false;

        return _onSame(rhs);
    }

    wbool me::isSub(const type& it) const { return getType().isSub(it); }
    wbool me::isSuper(const type& it) const { return getType().isSuper(it); }

    void* me::cast(const type& to) {
        if(!getType().isSub(to))
            return nullptr;

        return this;
    }
}
