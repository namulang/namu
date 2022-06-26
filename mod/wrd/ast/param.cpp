#include "param.hpp"
#include "node.hpp"

namespace wrd {
    WRD_DEF_ME(param)

    me::param(const std::string& newName, const wtype& orgType): _name(newName) {
        setOrgType(orgType);
    }

    me::param(const std::string& newName, const node& org) {
        setOrgType(org.getType());
    }

    void me::setOrgType(const wtype& newType) {
        _type = &newType;
    }

    const std::string& me::getName() const { return _name; }

    void me::setName(const std::string& new1) { _name = new1; }

    const wtype& me::getOrgType() const { return *_type; }
}
