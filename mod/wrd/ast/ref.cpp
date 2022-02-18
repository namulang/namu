#include "ref.hpp"
#include "refTactic.hpp"
#include "node.hpp"

namespace wrd {

    WRD_DEF_ME(ref)

    ref::ref(const std::string& name): _name(name), _ref(refTactic::_singletone) {
        setType(ttype<node>::get());
    }
    ref::ref(const node& it, const std::string& name): _ref(refTactic::_singletone) {
        setType(it.getType());
        bind(it);
    }
    ref::ref(const node* it, const std::string& name): _name(name), _ref(refTactic::_singletone) {
        setType(it->getType());
        bind(it);
    }
    ref::ref(const me& rhs): _name(rhs._name), _ref(refTactic::_singletone) {
        setType(rhs.getType());
        _assign(rhs);
    }

    me& ref::_assign(const me& rhs) {
        bind(*rhs);
        return *this;
    }
}
