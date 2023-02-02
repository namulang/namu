#include "nBool.hpp"
#include "../../ast/defaultCtor.hpp"
#include "../../ast/defaultCopyCtor.hpp"
#include "nInt.hpp"
#include "nFlt.hpp"
#include "nChar.hpp"
#include "nStr.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(nBool), DEF_VISIT())

    nbool me::wBoolType::isImmutable() const { return true; }

    me::nBool() {}
    me::nBool(nbool val): super(val) {}

    dumScope* me::_onMakeSubs() const {
        static nBool inner;
        scope scapegoat;
        scapegoat.add(baseObj::CTOR_NAME, new defaultCtor(inner));
        scapegoat.add(baseObj::CTOR_NAME, new defaultCopyCtor(inner));
        return new dumScope(scapegoat);
    }

    const ases& me::wBoolType::_getImpliAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            inner.add(new asPrimitive<nFlt, nbool>());
            inner.add(new asPrimitive<nChar, nbool>());
            inner.add(new asPrimitive<nInt, nbool>());
        }

        return inner;
    }

    const ases& me::wBoolType::_getAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            struct asStr : public tas<nStr> {
                str as(const node& me, const type& to) const override {
                    return str(new nStr(me.cast<nbool>() ? "true" : "false"));
                }
            };
            inner.add(new asStr());
        }

        return inner;
    }
}
