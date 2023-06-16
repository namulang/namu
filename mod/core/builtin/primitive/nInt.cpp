#include "nInt.hpp"
#include "../../ast/param.hpp"
#include "../../ast/defaultCtor.hpp"
#include "../../ast/defaultCopyCtor.hpp"
#include "nFlt.hpp"
#include "nByte.hpp"
#include "nChar.hpp"
#include "nBool.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(nInt), DEF_VISIT())

    void me::_onMakeSubs(scope& tray) const {
        static nInt inner;
        tray.add(baseObj::CTOR_NAME, new defaultCtor(inner));
        tray.add(baseObj::CTOR_NAME, new defaultCopyCtor(inner));
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
            inner.add(new asPrimitive<nChar, nint>());
            struct asStr : public tas<nStr> {
                str as(const node& me, const type& to) const override {
                    return new nStr(std::to_string(me.cast<nint>()));
                }
            };
            inner.add(new asStr());
        }

        return inner;
    }

    me::nInt() {}
    me::nInt(nint val): super(val) {}
}
