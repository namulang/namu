#include "param.hpp"
#include "node.hpp"

namespace wrd {
    WRD_DEF_ME(param)

    me::param(const std::string& newName, const node& origin): _name(newName), _org(origin.getType()) {
        setOrigin(origin);
    }

    void me::setOrigin(const node& new1) {
        _org.bind(new1);
    }

    const std::string& me::getName() const { return _name; }

    void me::setName(const std::string& new1) { _name = new1; }

    const str& me::getOrigin() const { return _org; }
}
