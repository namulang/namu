#include "node.hpp"
#include "ref.hpp"
#include "../builtin/container/native/nchain.hpp"
#include "../builtin/container/native/tnarr.inl"
#include "../builtin/container/native/ncontainer.inl"

namespace wrd {

    WRD_DEF_ME(node)

    ref me::as(const wtype& to) const {
        return getType().as(*this, to);
    }

    ref me::asImpli(const wtype& to) const {
        return getType().asImpli(*this, to);
    }

    narr me::sub(const std::string& name) const {
        return subs().get([&](const node& elem) {
            return elem.getName() == name;
        });
    }

    str me::run() {
        static narr empty;
        return run(empty);
    }
}
