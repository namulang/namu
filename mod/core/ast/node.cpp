#include "node.inl"
#include "scope.inl"
#include "../builtin/container/native/tnarr.inl"
#include "../type/as.hpp"
#include "args.hpp"
#include "../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(node), DEF_VISIT())

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
}
