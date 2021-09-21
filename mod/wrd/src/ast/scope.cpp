#include "scope.hpp"
#include "../builtin/container/native/tnarr.inl"
#include "../builtin/container/native/tnchain.inl"
#include "node.hpp"
#include "ref.hpp"

namespace wrd {

    WRD_DEF_ME(scope)

    wbool me::add(widx n, const node& new1) {
        const node* toAdd = &new1;
        if(nul(new1)) return false;
        if(!new1.isSub<ref>() && new1.getType().isImmutable())
            toAdd = new ref(new1);

        return super::add(n, *toAdd);
    }
}
