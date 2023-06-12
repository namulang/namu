#include "nByte.hpp"
#include "../../ast/defaultCtor.hpp"
#include "../../ast/defaultCopyCtor.hpp"
#include "nInt.hpp"
#include "nFlt.hpp"
#include "nBool.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(nByte), DEF_VISIT())

    nbool me::nByteType::isImmutable() const { return true; }

    const ases& me::nByteType::_getImpliAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            inner.add(new asPrimitive<nBool, nuchar>());
            inner.add(new asPrimitive<nInt, nuchar>());
        }

        return inner;
    }

    const ases& me::nByteType::_getAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            inner.add(new asPrimitive<nFlt, nuchar>());
            struct asStr : public tas<nStr> {
                str as(const node& me, const type& to) const override {
                    std::string val;
                    val.push_back(me.cast<nuchar>());
                    return str(new nStr(val));
                }
            };
            inner.add(new asStr());
        }

        return inner;
    }

    me::nByte() {}
    me::nByte(nuchar val): super(val) {}

    void me::_onMakeSubs(scope& tray) const {
        static nByte inner;
        tray.add(baseObj::CTOR_NAME, new defaultCtor(inner));
        tray.add(baseObj::CTOR_NAME, new defaultCopyCtor(inner));
    }
}
