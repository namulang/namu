#include "nChar.hpp"
#include "../../ast/defaultCtor.hpp"
#include "../../ast/defaultCopyCtor.hpp"
#include "nInt.hpp"
#include "nFlt.hpp"
#include "nBool.hpp"
#include "../../ast/visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(nChar), DEF_VISIT())

    nbool me::wCharType::isImmutable() const { return true; }

    const ases& me::wCharType::_getImpliAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            inner.add(new asPrimitive<nBool, nchar>());
        }

        return inner;
    }

    const ases& me::wCharType::_getAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            inner.add(new asPrimitive<nInt, nchar>());
            inner.add(new asPrimitive<nFlt, nchar>());
            struct asStr : public tas<nStr> {
                str as(const node& me, const type& to) const override {
                    std::string val;
                    val.push_back(me.cast<nchar>());
                    return str(new nStr(val));
                }
            };
            inner.add(new asStr());
        }

        return inner;
    }

    me::nChar() {}
    me::nChar(nchar val): super(val) {}

    dumScope* me::_onMakeCtors() const {
        static nChar inner;
        scope scapegoat;
        scapegoat.add(baseObj::CTOR_NAME, new defaultCtor(inner));
        scapegoat.add(baseObj::CTOR_NAME, new defaultCopyCtor(inner));
        return new dumScope(scapegoat);
    }
}
