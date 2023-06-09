#include "nInt.hpp"
#include "../../ast/param.hpp"
#include "../../ast/defaultCtor.hpp"
#include "../../ast/defaultCopyCtor.hpp"
#include "nFlt.hpp"
#include "nByte.hpp"
#include "nBool.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(nInt), DEF_VISIT())

    dumScope* me::_onMakeSubs() const {
        static nInt inner;
        scope scapegoat;
        scapegoat.add(baseObj::CTOR_NAME, new defaultCtor(inner));
        scapegoat.add(baseObj::CTOR_NAME, new defaultCopyCtor(inner));
        return new dumScope(scapegoat);
    }

    nbool me::wIntType::isImmutable() const { return true; }

    const ases& me::wIntType::_getImpliAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            inner.add(new asPrimitive<nFlt, nint>());
            inner.add(new asPrimitive<nByte, nint>());
            inner.add(new asPrimitive<nBool, nint>());
        }

        return inner;
    }

    const ases& me::wIntType::_getAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            struct asStr : public tas<nStr> {
                str as(const node& me, const type& to) const override {
                    nint val = me.cast<nint>();
                    NAMU_E("------------val=%d", val);
                    nStr* ret = new nStr(std::to_string(me.cast<nint>()));
                    NAMU_E("------------ret=%s", ret->get().c_str());

                    return str(ret);
                }
            };
            inner.add(new asStr());
        }

        return inner;
    }

    me::nInt() {}
    me::nInt(nint val): super(val) {}
}
