#include "nFlt.hpp"
#include "../../ast/defaultCtor.hpp"
#include "../../ast/defaultCopyCtor.hpp"
#include "nInt.hpp"
#include "nChar.hpp"
#include "nBool.hpp"
#include "../../ast/visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(nFlt), DEF_VISIT())

    nbool me::wFltType::isImmutable() const { return true; }

    const ases& me::wFltType::_getImpliAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            inner.add(new asPrimitive<nInt, nflt>());
            inner.add(new asPrimitive<nChar, nflt>());
            inner.add(new asPrimitive<nBool, nflt>());
        }

        return inner;
    }

    const ases& me::wFltType::_getAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            struct asStr : public tas<nStr> {
                str as(const node& me, const type& to) const override {
                    return str(new nStr(std::to_string(me.cast<nflt>())));
                }
            };
            inner.add(new asStr());
        }

        return inner;
    }

    me::nFlt() {}
    me::nFlt(nflt val): super(val) {}

    dumScope* me::_onMakeCtors() const {
        static nFlt inner;
        scope scapegoat;
        scapegoat.add(baseObj::CTOR_NAME, new defaultCtor(inner));
        scapegoat.add(baseObj::CTOR_NAME, new defaultCopyCtor(inner));
        return new dumScope(scapegoat);
    }
}
