#include "wBool.hpp"
#include "../../ast/mgd/defaultCtor.hpp"
#include "../../ast/mgd/defaultCopyCtor.hpp"
#include "wStr.hpp"

namespace wrd {

    WRD_DEF_ME(wBool)

    wbool me::wBoolType::isImmutable() const { return true; }

    const ases& me::wBoolType::_getImpliAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            struct toWstr: public tas<wStr> {
                str as(const node& wBool, const type& to) const override {
                    // TODO:
                    return str();
                }
            };
            inner.add(new toWstr());
        }

        return inner;
    }

    me::wBool() {}
    me::wBool(wbool val): super(val) {}

    dumScope* me::_onMakeCtors() const {
        scope scapegoat;
        scapegoat.add(obj::CTOR_NAME, new defaultCtor(getType()));
        scapegoat.add(obj::CTOR_NAME, new defaultCopyCtor(getType()));
        return new dumScope(scapegoat);
    }
}
