#include "wFlt.hpp"
#include "../../ast/defaultCtor.hpp"
#include "../../ast/defaultCopyCtor.hpp"
#include "wInt.hpp"
#include "wChar.hpp"
#include "wBool.hpp"

namespace wrd {

    WRD_DEF_ME(wFlt)

    wbool me::wFltType::isImmutable() const { return true; }

    const ases& me::wFltType::_getImpliAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            inner.add(new asPrimitive<wInt, wflt>());
            inner.add(new asPrimitive<wChar, wflt>());
            inner.add(new asPrimitive<wBool, wflt>());
        }

        return inner;
    }

    const ases& me::wFltType::_getAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            struct asStr : public tas<wStr> {
                str as(const node& me, const type& to) const override {
                    return str(new wStr(std::to_string(me.cast<wflt>())));
                }
            };
            inner.add(new asStr());
        }

        return inner;
    }

    me::wFlt() {}
    me::wFlt(wflt val): super(val) {}

    dumScope* me::_onMakeCtors() const {
        scope scapegoat;
        scapegoat.add(baseObj::CTOR_NAME, new defaultCtor(getType()));
        scapegoat.add(baseObj::CTOR_NAME, new defaultCopyCtor(getType()));
        return new dumScope(scapegoat);
    }
}
