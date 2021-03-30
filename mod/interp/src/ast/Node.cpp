#include "Node.hpp"
#include "Ref.hpp"

namespace wrd {

    WRD_DEF_THIS(Node)

    Ref This::as(const WType& to) const {
        return getType().as(*this, to);
    }

    Ref This::asImpli(const WType& to) const {
        return getType().asImpli(*this, to);
    }

}
