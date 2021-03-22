#include "WType.hpp"
#include "../ast/Ref.hpp"

namespace wrd {

    WRD_DEF_THIS(WType)

    Ref This::impliAs(const Node& inst) const {
        const Type& type = inst.getType();
        if(type.isSuper(*this)) return Ref(inst);

        for(auto e : _getImplis())
            if(e->is(type)) return e->as(inst);
        return Ref();
    }

    Ref This::as(const Node& it) const {
        Ref ret = impliAs(it);
        if(ret) return ret;

        // TODO:
        return Ref();
    }
}
