#include "Node.hpp"
#include "Ref.hpp"

namespace wrd {

    WRD_DEF_THIS(Node)

    Ref This::as(const This& it) const {
        return getType().as(it);
    }

    Ref This::impliAs(const Node& inst) const {
        return getType().impliAs(inst);
    }

}
