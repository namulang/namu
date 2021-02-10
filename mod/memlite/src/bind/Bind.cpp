#include "Bind.hpp"
#include "../watcher/BindTag.hpp"
#include "BindTacticable.hpp"
#include "TBindable.inl"

namespace wrd {

    WRD_DEF_THIS(Bind)

    Bind::Bind(BindTacticable* tactic): _tactic(tactic) {
        if(!tactic) WRD_W("tactic == null");
    }

    Bind::Bind(This& rhs): _tactic(rhs._tactic) { _assign(rhs); }
    Bind::~Bind() { This::unbind(); }
    wbool This::operator==(This& rhs) { return &get() == &rhs.get(); }
    wbool This::operator!=(This& rhs) { return ! operator==(rhs); }

    This& This::operator=(This& rhs) {
        if(this == &rhs) return *this;

        _assign(rhs);
        return *this;
    }

    wbool This::isBind() {
        BindTag& tag = _getBindTag(_itsId);
        if(nul(tag)) return false;

        return tag.isBind();
    }

    wbool This::unbind() {
        return _tactic->unbind(*this);
    }

    Id This::getItsId() { return _itsId; }
    wbool This::canBind(Type& type) { return getType().isSuper(type); }
    Type& This::getType() { return _tactic->getType(); }

    wbool This::_bind(Instance& it) {
        if(!TBindable<Instance>::_bind(it)) return false;

        return _tactic->bind(*this, it);
    }

    Instance& This::_get() {
        Instance& ins = WRD_GETS(_getBindTag(_itsId),get());
        WRD_NUL_THEN_LOG(ins)

        return ins;
    }

    wbool This::_assign(Bind& rhs) {
        return _tactic->assign(*this, rhs);
    }

#undef This
}
