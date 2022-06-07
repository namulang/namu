#include "wInt.hpp"
#include "../../ast/param.hpp"
#include "../../ast/mgd/defaultCtor.hpp"
#include "../../ast/mgd/defaultCopyCtor.hpp"

namespace wrd {

    WRD_DEF_ME(wInt)

    void me::_onMakeCtors(scope& tray) const {
        tray.add(obj::CTOR_NAME, new defaultCtor(getType()));
        tray.add(obj::CTOR_NAME, new defaultCopyCtor(getType()));
    }

    wbool me::wIntType::isImmutable() const { return true; }

    const ases& me::wIntType::_getImpliAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            struct toWstr: public tas<wStr> {
                str as(const node& wInt, const type& to) const override {
                    // TODO:
                    return str();
                }
            };
            inner.add(new toWstr());
        }

        return inner;
    }

    me::wInt() {}
    me::wInt(wint val): super(val) {}
}
