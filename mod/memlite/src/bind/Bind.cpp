#include "Bind.hpp"
#include "../watcher/BindTag.hpp"
#include "BindTacticable.hpp"
#include "TBindable.inl"

namespace wrd {

    WRD_DEF_ME(Bind)

    Bind::Bind(const Type& type, BindTacticable& tactic): _type(&type.getStatic()), _tactic(&tactic) {}
    Bind::Bind(const me& rhs): _type(rhs._type), _tactic(rhs._tactic) { _assign(rhs); }
    Bind::~Bind() { me::unbind(); }

    me& me::operator=(const me& rhs) {
        if(this == &rhs) return *this;

        _assign(rhs);
        return *this;
    }

    wbool me::isBind() const {
        const BindTag& tag = _getBindTag();
        if(nul(tag)) return false;

        return tag.isBind();
    }

    wbool me::unbind() {
        return _tactic->unbind(*this);
    }

    Id me::getItsId() const { return _itsId; }
    wbool me::canBind(const Type& type) const { return getType().isSuper(type); }
    const Type& me::getType() const { return *_type; }

    wbool me::bind(const Instance& it) {
        if(!TBindable<Instance>::bind(it)) return false;

        return _tactic->bind(*this, it);
    }

    Instance& me::get() {
        return WRD_GETS(_getBindTag(),get());
    }

    wbool me::_assign(const Bind& rhs) {
        unbind();
        _type = rhs._type;
        if (nul(_tactic))
            _tactic = rhs._tactic;
        return bind(rhs.get());
    }

    wbool me::_onSame(const TypeProvidable& rhs) const {
        const me& cast = (const me&) rhs;
        return get() == cast.get();
    }

    BindTag& me::_getBindTag() const {
        return const_cast<BindTag&>(BindTag::getBindTag(_itsId));
    }
}
