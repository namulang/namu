#include "nVoid.hpp"
#include "../../ast/defaultCtor.hpp"
#include "../../ast/defaultCopyCtor.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(nVoid), DEF_VISIT())

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

    dumScope* me::_onMakeSubs() const {
        static nVoid inner;
        scope scapegoat;
        scapegoat.add(baseObj::CTOR_NAME, new defaultCtor(inner));
        scapegoat.add(baseObj::CTOR_NAME, new defaultCopyCtor(inner));
        return new dumScope(scapegoat);
    }
}
