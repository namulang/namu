#include "wVoid.hpp"
#include "../../ast/mgd/defaultCtor.hpp"
#include "../../ast/mgd/defaultCopyCtor.hpp"

namespace wrd {

    WRD_DEF_ME(wVoid)

    wbool me::wVoidType::isImmutable() const { return true; }

    const ases& me::wVoidType::_getImpliAses() const {
        static ases inner;
        return inner;
    }

    me::wVoid() {}

    me& me::singletone() {
        static me inner;
        return inner;
    }

    void me::_onMakeCtors(scope& tray) const {
        tray.add(obj::CTOR_NAME, new defaultCtor(getType()));
        tray.add(obj::CTOR_NAME, new defaultCopyCtor(getType()));
    }
}
