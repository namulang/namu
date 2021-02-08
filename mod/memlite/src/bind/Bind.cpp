#include "Bind.hpp"
#include "../watcher/BindTag.hpp"
#include "BindTacticable.hpp"
#include "TBindable.inl"

namespace wrd {

    WRD_DEF_THIS(Bind)

    Bind::Bind(BindTacticable* tactic): _tactic(tactic) {
        if(!tactic) WRD_W("tactic == null");
    }

    Bind::Bind(const This& rhs): _tactic(rhs._tactic) { _assign(rhs); }
    Bind::~Bind() { This::unbind(); }
    wbool This::operator==(const This& rhs) const { return &get() == &rhs.get(); }
    wbool This::operator!=(const This& rhs) const { return ! operator==(rhs); }

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
    wbool This::isConst() const { return _tactic->isConst(); }
    wbool This::canBind(const Type& type) const { return getType().isSuper(type); }
    const Type& This::getType() const { return _tactic->getType(); }

    wbool This::_bind(const Instance& it) {
        if(!TBindable<Instance>::_bind(it)) return false;

        return _tactic->bind(*this, it);
    }

    Instance& This::_get() {
        Instance& ins = WRD_GETS(_getBindTag(_itsId),get());
        WRD_NUL_THEN_LOG(ins)

        return ins;
    }

    wbool This::_assign(const Bind& rhs) {
        return _tactic->assign(*this, rhs);
    }

#undef This
}
