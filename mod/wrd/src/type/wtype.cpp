#include "wtype.hpp"
#include "../ast/ref.hpp"

namespace wrd {

    WRD_DEF_ME(wtype)

    ref me::asImpli(const node& it, const wtype& to) const {
        const type& type = it.getType();
        if(!type.isSuper(*this)) return WRD_W("given instance 'it' wasn't subclass of %s", getName().c_str()), ref();
        if(to.isSuper(*this)) return ref(it);

        for(auto e : _getImplis())
            if(e->is(to)) return e->as(it);
        return ref();
    }

    ref me::as(const node& it, const wtype& to) const {
        ref ret = asImpli(it, to);
        if(ret) return ret;

        // TODO:
        return ref();
    }
}
