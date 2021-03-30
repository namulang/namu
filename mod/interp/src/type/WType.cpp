#include "WType.hpp"
#include "../ast/Ref.hpp"

namespace wrd {

    WRD_DEF_THIS(WType)

    Ref This::asImpli(const Node& it, const WType& to) const {
        const Type& type = it.getType();
        if(!type.isSuper(*this)) return WRD_W("given instance 'it' wasn't subclass of %s", getName().c_str()), Ref();
        if(to.isSuper(*this)) return Ref(it);

        for(auto e : _getImplis())
            if(e->is(to)) return e->as(it);
        return Ref();
    }

    Ref This::as(const Node& it, const WType& to) const {
        Ref ret = asImpli(it, to);
        if(ret) return ret;

        // TODO:
        return Ref();
    }
}
