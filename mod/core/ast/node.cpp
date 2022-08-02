#include "node.inl"
#include "scope.inl"
#include "../builtin/container/native/tnarr.inl"
#include "../type/as.hpp"
#include "../loader/interpreter/tverification.hpp"
#include "../loader/interpreter/verification.inl"
#include "../loader/interpreter/verifier.hpp"
#include "params.hpp"

namespace namu {

    WRD_DEF_ME(node)

    node& me::operator[](const std::string& name) const {
        return sub(name);
    }

    str me::run() {
        return run(narr());
    }

    str me::run(const std::string& name) {
        return run(name, narr());
    }

    str me::run(const std::string& name, const ucontainable& args) {
        if(name.empty()) return run(args);
        me& found = sub(name, args);
        if(nul(found)) return str();

        return _onRunSub(found, args);
    }

    wbool me::is(const typeProvidable& to) const { return is(to.getType()); }
    wbool me::is(const type& to) const { return getType().is(to); }
    str me::as(const typeProvidable& to) const { return as(to.getType()); }
    str me::as(const type& to) const { return getType().as(*this, to); }

    wbool me::isImpli(const typeProvidable& to) const { return isImpli(to.getType()); }
    wbool me::isImpli(const type& to) const { return getType().isImpli(to); }
    str me::asImpli(const typeProvidable& to) const { return asImpli(to.getType()); }
    str me::asImpli(const type& to) const { return getType().asImpli(*this, to); }

    const node& me::getEval() const {
        return *this;
    }

    str me::_onRunSub(node& sub, const ucontainable& args) {
        return sub.run(args);
    }



    WRD_VERIFY({ // no same variable.
        WRD_DI("verify: node: no same variable=%d", it.subs().len());
        if(it.isSub<frame>()) return;

        for(auto e=it.subs().begin(); e ;++e) {
            if(it.subAll<baseObj>(e.getKey()).len() > 1)
                return _err(e->getPos(), errCode::DUP_VAR, e.getKey().c_str());
        }
    })
}
