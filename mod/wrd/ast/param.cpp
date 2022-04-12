#include "param.hpp"
#include "node.hpp"

namespace wrd {
    WRD_DEF_ME(param)

    me::param(const std::string& newName, const node& origin): _name(newName), _type(&origin.getType()) {
        setOrigin(origin);
    }

    void me::setOrigin(const node& new1) {
        if(!new1.getType().isSub(*_type)) {
            WRD_W("param: given new1[%s] is not sub of type %s", new1.getType().getName().c_str(),
                _type->getName().c_str());
            return;
        }

        _org.bind(new1);
    }
}
