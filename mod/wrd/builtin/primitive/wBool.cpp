#include "wBool.hpp"
#include "../../ast/mgd/defaultCtor.hpp"
#include "../../ast/mgd/defaultCopyCtor.hpp"
#include "wInt.hpp"
#include "wFlt.hpp"
#include "wChar.hpp"

namespace wrd {

    WRD_DEF_ME(wBool)

    wbool me::wBoolType::isImmutable() const { return true; }

    me::wBool() {}
    me::wBool(wbool val): super(val) {}

    dumScope* me::_onMakeCtors() const {
        scope scapegoat;
        scapegoat.add(obj::CTOR_NAME, new defaultCtor(getType()));
        scapegoat.add(obj::CTOR_NAME, new defaultCopyCtor(getType()));
        return new dumScope(scapegoat);
    }
}
