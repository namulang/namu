#include "nVoid.hpp"
#include "../../ast/defaultCtor.hpp"
#include "../../ast/defaultCopyCtor.hpp"

namespace namu {

    NAMU_DEF_ME(nVoid)

    nbool me::wVoidType::isImmutable() const { return true; }

    const ases& me::wVoidType::_getImpliAses() const {
        static ases inner;
        return inner;
    }

    me::nVoid() {}

    me& me::singletone() {
        static me inner;
        return inner;
    }

    dumScope* me::_onMakeCtors() const {
        scope scapegoat;
        scapegoat.add(baseObj::CTOR_NAME, new defaultCtor(*this));
        scapegoat.add(baseObj::CTOR_NAME, new defaultCopyCtor(*this));
        return new dumScope(scapegoat);
    }
}
