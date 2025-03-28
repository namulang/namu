#include "ases.hpp"

#include "../../ast/node.hpp"
#include "../../builtin/primitive/nVoid.hpp"

namespace nm {

    NM_DEF_ME(ases)

    str me::as(const node& from, const type& to) const {
        const type& fromType = from.getType();
        WHEN(to.isSuper(fromType)).ret(str(from));

        for(aser& e: *this)
            if(e.is(fromType, to)) return e.as(from, to);
        // there is no null in namulang:
        //  returns void if no valid casting found.
        return str(nVoid::singletone());
    }

    nbool me::is(const type& from, const type& to) const {
        WHEN(to.isSuper(from)).ret(true);

        for(auto& e: *this)
            if(e.is(from, to)) return true;
        return false;
    }
} // namespace nm
