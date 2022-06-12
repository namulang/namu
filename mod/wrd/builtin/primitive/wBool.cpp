#include "wBool.hpp"
#include "../../ast/mgd/defaultCtor.hpp"
#include "../../ast/mgd/defaultCopyCtor.hpp"
#include "wInt.hpp"
#include "wFlt.hpp"
#include "wChar.hpp"

namespace wrd {

    WRD_DEF_ME(wBool)

    wbool me::wBoolType::isImmutable() const { return true; }

    const ases& me::wBoolType::_getImpliAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            inner.add(new asPrimitive<wInt, wint>());
            inner.add(new asPrimitive<wFlt, wflt>());
            inner.add(new asPrimitive<wChar, wchar>());
        }

        return inner;
    }

    me::wBool() {}
    me::wBool(wbool val): super(val) {}

    dumScope* me::_onMakeCtors() const {
        scope scapegoat;
        scapegoat.add(obj::CTOR_NAME, new defaultCtor(getType()));
        scapegoat.add(obj::CTOR_NAME, new defaultCopyCtor(getType()));
        return new dumScope(scapegoat);
    }
}
