#include "scopes.hpp"
#include "../builtin/container/native/tnchain.inl"

namespace namu {
    
    NAMU(DEF_ME(scopes))

    me::scopes() {}
    me::scopes(const super::super& arr): super(arr) {}
    me::scopes(const super::super* arr): super(arr) {}

    node& me::getOwner() { return *_owner; }
    void me::setOwner(const node& owner) { _owner.bind(owner); }
    me* me::deepClone() const { return (me*) super::deepClone(); }

    me* me::wrap(const super::super& toShallowWrap) const {
        return (me*) wrap<me>(toShallowWrap);
    }

    me* me::wrapDeep(const super::super& toDeepWrap) const {
        return (me*) wrapDeep<me>(toDeepWrap);
    }
}
