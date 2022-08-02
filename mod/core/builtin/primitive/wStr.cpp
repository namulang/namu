#include "wStr.hpp"
#include "../../ast/defaultCtor.hpp"
#include "../../ast/defaultCopyCtor.hpp"
#include "wBool.hpp"
#include "wInt.hpp"
#include "wFlt.hpp"
#include "wChar.hpp"

namespace namu {

    WRD_DEF_ME(wStr)

    wbool me::wStrType::isImmutable() const { return true; }

    me::wStr() {}
    me::wStr(const wchar* val): super(std::string(val)) {}
    me::wStr(const std::string& val): super(val) {}

    dumScope* me::_onMakeCtors() const {
        static wStr inner;
        scope scapegoat;
        scapegoat.add(baseObj::CTOR_NAME, new defaultCtor(inner));
        scapegoat.add(baseObj::CTOR_NAME, new defaultCopyCtor(inner));
        return new dumScope(scapegoat);
    }

    const ases& me::wStrType::_getAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            struct asBool : public tas<wBool> {
                str as(const node& me, const type& to) const override {
                    const std::string& val = me.cast<std::string>();
                    try {
                        bool boolean = false;
                        if(val == "false")
                            boolean = false;
                        else if(val == "true")
                            boolean = "true";
                        else
                            boolean = stoi(val) == 0;
                        return str(new wBool(boolean));
                    } catch (std::invalid_argument& ex) {
                        return str();
                    }
                }
            };
            inner.add(new asBool());
            struct asFlt : public tas<wFlt> {
                str as(const node& me, const type& to) const override {
                    const std::string& val = me.cast<std::string>();
                    try {
                        return str(new wFlt(stof(val)));
                    } catch (std::invalid_argument& ex) {
                        return str();
                    }
                }
            };
            inner.add(new asFlt());
            struct asInt: public tas<wInt> {
                str as(const node& me, const type& to) const override {
                    const std::string& val = me.cast<std::string>();
                    try {
                        return str(new wInt(stoi(val)));
                    } catch (std::invalid_argument& ex) {
                        return str();
                    }
                }
            };
            inner.add(new asInt());
            struct asChar : public tas<wChar> {
                str as(const node& me, const type& to) const override {
                    const std::string& val = me.cast<std::string>();
                    if (val.length() > 1) return str();

                    return str(new wChar(val.at(0)));
                }
            };
            inner.add(new asChar());
        }

        return inner;
    }
}
