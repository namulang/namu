#include "param.hpp"
#include "node.hpp"

namespace wrd {
    WRD_DEF_ME(param)

    me::param(const std::string& newName, const node& origin): _name(newName), _org(origin.getType()) {
        setOrigin(origin);
    }

    void me::setOrigin(const node& new1) {
        _org = str(new1.getType());
        _org.bind(new1);
    }

    void me::setOrigin(const wtype& new1) {
        _org = str(new1);
    }
}
