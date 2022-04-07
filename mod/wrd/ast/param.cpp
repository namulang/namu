#include "param.hpp"
#include "node.hpp"

namespace wrd {
    WRD_DEF_ME(param)

    void me::setOrigin(const node& new1) {
        setOrigin(new1.getType());
        _org.bind(new1);
    }
}
