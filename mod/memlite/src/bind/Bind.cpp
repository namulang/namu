#include "Bind.hpp"
#include "../watcher/BindTag.hpp"
#include "BindTacticable.hpp"
#include "TBindable.inl"

namespace wrd {

    WRD_DEF_THIS(Bind)

    Bind::Bind(const Type& type, BindTacticable& tactic): _type(&type.getStatic()), _tactic(&tactic) {}
    Bind::Bind(const This& rhs): _type(rhs._type), _tactic(rhs._tactic) { _assign(rhs); }
    Bind::~Bind() { This::unbind(); }

    This& This::operator=(const This& rhs) {
        if(this == &rhs) return *this;

        _assign(rhs);
        return *this;
    }

    wbool This::isBind() const {
        const BindTag& tag = _getBindTag(_itsId);
        if(nul(tag)) return false;

        return tag.isBind();
    }

    wbool This::unbind() {
        return _tactic->unbind(*this);
    }

    Id This::getItsId() const { return _itsId; }
    wbool This::canBind(const Type& type) const { return getType().isSuper(type); }
    const Type& This::getType() const { return *_type; }

    wbool This::bind(const Instance& it) {
        if(!TBindable<Instance>::bind(it)) return false;

        return _tactic->bind(*this, it);
    }

    Instance& This::get() {
        return WRD_GETS(_getBindTag(_itsId),get());
    }

    wbool This::_assign(const Bind& rhs) {
        unbind();
        _type = rhs._type;
        _tactic = rhs._tactic;
        return bind(rhs.get());
    }

    wbool This::_onSame(const TypeProvidable& rhs) const {
        const This& cast = (const This&) rhs;
        return get() == cast.get();
    }
}
