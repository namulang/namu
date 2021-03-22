#include "Asable.inl"

namespace wrd {

    WRD_DEF_THIS(Asable)

    wbool This::is(const Node& inst) const {
        return is(inst.getType());
    }

}
