#include "wtype.hpp"
#include "../ast/node.hpp"

namespace wrd {

    WRD_DEF_ME(wtype)

    wbool me::isImpli(const type& to) const {
        return _getImpliAses().is(*this, to);
    }
    wbool me::isImpli(const typeProvidable& to) const { return isImpli(to.getType()); }

    str me::asImpli(const node& from, const type& to) const {
        return _getImpliAses().as(from, to);
    }

    wbool me::is(const type& to) const {
        if(isImpli(to)) return true;

        return _getAses().is(*this, to);
    }

    str me::as(const node& from, const type& to) const {
        if(isImpli(to))
            return asImpli(from, to);

        return _getAses().as(from, to);
    }

    wbool me::isImmutable() const {
        return false;
    }

    const ases& me::_getImpliAses() const {
        static ases inner;
        return inner;
    }

    const ases& me::_getAses() const {
        static ases inner;
        return inner;
    }
}
