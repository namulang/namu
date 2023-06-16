#include "nChar.hpp"
#include "../../ast/defaultCtor.hpp"
#include "../../ast/defaultCopyCtor.hpp"
#include "nInt.hpp"
#include "nFlt.hpp"
#include "nBool.hpp"
#include "nByte.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(nChar), DEF_VISIT())

    nbool me::nCharType::isImmutable() const { return true; }

    const ases& me::nCharType::_getImpliAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            inner.add(new asPrimitive<nBool, nchar>());
            inner.add(new asPrimitive<nInt, nchar>());
            inner.add(new asPrimitive<nByte, nchar>());
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

    const ases& me::nCharType::_getAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            inner.add(new asPrimitive<nFlt, nchar>());
        }

        return inner;
    }

    me::nChar() {}
    me::nChar(nchar val): super(val) {}

    void me::_onMakeSubs(scope& tray) const {
        static nChar inner;
        tray.add(baseObj::CTOR_NAME, new defaultCtor(inner));
        tray.add(baseObj::CTOR_NAME, new defaultCopyCtor(inner));
    }
}
