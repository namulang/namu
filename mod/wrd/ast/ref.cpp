#include "ref.hpp"
#include "refTactic.hpp"
#include "node.hpp"

namespace wrd {

    WRD_DEF_ME(ref)

    ref::ref(const std::string& name): _name(name), _ref(refTactic::_singletone) {
        _setType(ttype<node>::get());
    }
    ref::ref(const node& it, const std::string& name): _ref(refTactic::_singletone) {
        _setType(it.getType());
        bind(it);
    }
    ref::ref(const node* it, const std::string& name): _name(name), _ref(refTactic::_singletone) {
        _setType(it->getType());
        bind(it);
    }
    ref::ref(const me& rhs): _name(rhs._name), _ref(refTactic::_singletone) {
        _setType(rhs.getType());
        _assign(rhs);
    }

    ref::ref(const type& t, const std::string& name): _name(name), _ref(refTactic::_singletone) {
        _setType(t);
    }
    ref::ref(const node& it, const type& t, const std::string& name): _ref(refTactic::_singletone) {
        _setType(t);
        bind(it);
    }
    ref::ref(const node* it, const type& t, const std::string& name): _name(name), _ref(refTactic::_singletone) {
        _setType(t);
        bind(it);
    }
    ref::ref(const me& rhs, const type& t): _name(rhs._name), _ref(refTactic::_singletone) {
        _setType(t);
        _assign(rhs);
    }

    me& ref::_assign(const me& rhs) {
        bind(*rhs);
        return *this;
    }
}
