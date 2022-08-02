#include "wInt.hpp"
#include "../../ast/param.hpp"
#include "../../ast/defaultCtor.hpp"
#include "../../ast/defaultCopyCtor.hpp"
#include "wFlt.hpp"
#include "wChar.hpp"
#include "wBool.hpp"

namespace namu {

    WRD_DEF_ME(wInt)

    dumScope* me::_onMakeCtors() const {
        static wInt inner;
        scope scapegoat;
        scapegoat.add(baseObj::CTOR_NAME, new defaultCtor(inner));
        scapegoat.add(baseObj::CTOR_NAME, new defaultCopyCtor(inner));
        return new dumScope(scapegoat);
    }

    wbool me::wIntType::isImmutable() const { return true; }

    const ases& me::wIntType::_getImpliAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            inner.add(new asPrimitive<wFlt, wflt>());
            inner.add(new asPrimitive<wChar, wchar>());
            inner.add(new asPrimitive<wBool, wbool>());
        }

        return inner;
    }

    const ases& me::wIntType::_getAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            struct asStr : public tas<wStr> {
                str as(const node& me, const type& to) const override {
                    wint val = me.cast<wint>();
                    WRD_E("------------val=%d", val);
                    wStr* ret = new wStr(std::to_string(me.cast<wint>()));
                    WRD_E("------------ret=%s", ret->get().c_str());

                    return str(ret);
                }
            };
            inner.add(new asStr());
        }

        return inner;
    }

    me::wInt() {}
    me::wInt(wint val): super(val) {}
}
