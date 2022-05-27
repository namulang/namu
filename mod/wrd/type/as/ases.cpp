#include "ases.hpp"
#include "../../ast/node.hpp"

namespace wrd {

    WRD_DEF_ME(ases)

    str me::as(const node& from, const type& to) const {
        const type& fromType = from.getType();
        if(to.isSuper(fromType)) return str(from);

        for(auto e : _casts)
            if(e->is(fromType, to))
                return e->as(from, to);
        return str();
    }
}
