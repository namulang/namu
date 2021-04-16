#include "Node.hpp"
#include "Ref.hpp"

namespace wrd {

    WRD_DEF_ME(Node)

    Ref me::as(const WType& to) const {
        return getType().as(*this, to);
    }

    Ref me::asImpli(const WType& to) const {
        return getType().asImpli(*this, to);
    }

}
