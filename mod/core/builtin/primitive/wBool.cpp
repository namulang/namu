#include "wBool.hpp"
#include "../../ast/defaultCtor.hpp"
#include "../../ast/defaultCopyCtor.hpp"
#include "wInt.hpp"
#include "wFlt.hpp"
#include "wChar.hpp"
#include "wStr.hpp"

namespace namu {

    WRD_DEF_ME(wBool)

    wbool me::wBoolType::isImmutable() const { return true; }

    me::wBool() {}
    me::wBool(wbool val): super(val) {}

    dumScope* me::_onMakeCtors() const {
        static wBool inner;
        scope scapegoat;
        scapegoat.add(baseObj::CTOR_NAME, new defaultCtor(inner));
        scapegoat.add(baseObj::CTOR_NAME, new defaultCopyCtor(inner));
        return new dumScope(scapegoat);
    }

    const ases& me::wBoolType::_getImpliAses() const {
        static ases inner;
        return inner;
    }

    const ases& me::wBoolType::_getAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            inner.add(new asPrimitive<wFlt, wbool>());
            inner.add(new asPrimitive<wInt, wbool>());
            inner.add(new asPrimitive<wChar, wbool>());
            struct asStr : public tas<wStr> {
                str as(const node& me, const type& to) const override {
                    return str(new wStr(me.cast<wbool>() ? "true" : "false"));
                }
            };
            inner.add(new asStr());
        }

        return inner;
    }
}
