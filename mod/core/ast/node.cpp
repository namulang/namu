#include "node.inl"
#include "scope.inl"
#include "../builtin/container/native/tnarr.inl"
#include "../type/as.hpp"
#include "../loader/interpreter/tverification.hpp"
#include "../loader/interpreter/verification.inl"
#include "../loader/interpreter/verifier.hpp"
#include "params.hpp"
#include "args.hpp"

namespace namu {

    NAMU_DEF_ME(node)

    node& me::operator[](const std::string& name) const {
        return sub(name);
    }

    str me::run() {
        return run(args());
    }

    str me::run(const std::string& name) {
        return run(name, args());
    }

    str me::run(const std::string& name, const args& a) {
        if(name.empty()) return run(a);
        me& found = sub(name, a);
        if(nul(found)) return str();

        return _onRunSub(found, a);
    }

    nbool me::is(const typeProvidable& to) const { return is(to.getType()); }
    nbool me::is(const type& to) const { return getType().is(to); }
    str me::as(const typeProvidable& to) const { return as(to.getType()); }
    str me::as(const type& to) const { return getType().as(*this, to); }

    nbool me::isImpli(const typeProvidable& to) const { return isImpli(to.getType()); }
    nbool me::isImpli(const type& to) const { return getType().isImpli(to); }
    str me::asImpli(const typeProvidable& to) const { return asImpli(to.getType()); }
    str me::asImpli(const type& to) const { return getType().asImpli(*this, to); }

    const node& me::getEval() const {
        return *this;
    }

    str me::_onRunSub(node& sub, const args& a) {
        return sub.run(a);
    }



    NAMU_VERIFY({ // no same variable.
        NAMU_DI("verify: node: no same variable=%d", it.subs().len());
        if(it.isSub<frame>()) return;

        for(auto e=it.subs().begin(); e ;++e) {
            if(it.subAll<baseObj>(e.getKey()).len() > 1)
                return _err(e->getPos(), errCode::DUP_VAR, e.getKey().c_str());
        }

        NAMU_DI("...verified: node: no same variable=%d", it.subs().len());
    })
}
