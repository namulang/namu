#include "node.hpp"
#include "ref.hpp"

namespace wrd {

    WRD_DEF_ME(node)

    ref me::as(const wtype& to) const {
        return getType().as(*this, to);
    }

    ref me::asImpli(const wtype& to) const {
        return getType().asImpli(*this, to);
    }

}
