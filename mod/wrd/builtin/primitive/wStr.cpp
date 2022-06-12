#include "wStr.hpp"
#include "wInt.hpp"
#include "../../ast/mgd/defaultCtor.hpp"
#include "../../ast/mgd/defaultCopyCtor.hpp"

namespace wrd {

    WRD_DEF_ME(wStr)

    wbool me::wStrType::isImmutable() const { return true; }

    me::wStr() {}
    me::wStr(const wchar* val): super(std::string(val)) {}
    me::wStr(const std::string& val): super(val) {}

    dumScope* me::_onMakeCtors() const {
        scope scapegoat;
        scapegoat.add(obj::CTOR_NAME, new defaultCtor(getType()));
        scapegoat.add(obj::CTOR_NAME, new defaultCopyCtor(getType()));
        return new dumScope(scapegoat);
    }
}
