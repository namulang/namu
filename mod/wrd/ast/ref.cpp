#include "ref.hpp"
#include "refTactic.hpp"
#include "node.hpp"

namespace wrd {

    WRD_DEF_ME(ref)

    ref::ref(const std::string& name): super(refTactic::_singletone), _name(name) {}
    ref::ref(const node& it, const std::string& name):
        super(refTactic::_singletone) { bind(it); }
    ref::ref(const node* it, const std::string& name):
        super(refTactic::_singletone), _name(name) { bind(it); }
    ref::ref(const me& rhs):
        super(refTactic::_singletone), _name(rhs._name) { _assign(rhs); }
    ref::ref(const binder& rhs): super(refTactic::_singletone) { _assign(rhs); }

    me& ref::_assign(const super& rhs) {
        bind(*rhs);

        const me& castRhs = rhs.cast<me>();
        if(!nul(castRhs))
            _name = castRhs._name;

        return *this;
    }
}
