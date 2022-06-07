#include "wStr.hpp"
#include "wInt.hpp"
#include "../../ast/mgd/defaultCtor.hpp"
#include "../../ast/mgd/defaultCopyCtor.hpp"

namespace wrd {

    WRD_DEF_ME(wStr)

    const ases& me::wStrType::_getImpliAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            struct toWInt: public tas<wInt> {
                str as(const node& wStr, const type& to) const override {
                    // TODO:
                    return str();
                }
            };
            inner.add(new toWInt());
        }

        return inner;
    }

    wbool me::wStrType::isImmutable() const { return true; }

    me::wStr() {}
    me::wStr(const wchar* val): super(std::string(val)) {}
    me::wStr(const std::string& val): super(val) {}

    void me::_onMakeCtors(scope& tray) const {
        tray.add(obj::CTOR_NAME, new defaultCtor(getType()));
        tray.add(obj::CTOR_NAME, new defaultCopyCtor(getType()));
    }
}
