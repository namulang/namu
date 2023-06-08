#include "nStr.hpp"
#include "../../ast/defaultCtor.hpp"
#include "../../ast/defaultCopyCtor.hpp"
#include "nBool.hpp"
#include "nInt.hpp"
#include "nFlt.hpp"
#include "nChar.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    namespace {
        class lenFunc : public APIBridge<nStr, nInt> {
            typedef APIBridge<nStr, nInt> __super__;
            NAMU(CLASS(lenFunc, __super__))

        protected:
            str _onRun(nStr& cast, const args& a) const override {
                return str(new nInt(cast.len()));
            }
        };

        class getFunc : public APIBridge<nStr, nStr> {
            typedef APIBridge<nStr, nStr> __super__;
            NAMU(CLASS(getFunc, __super__))

        protected:
            str _onRun(nStr& cast, const args& a) const override {
                if(a.len() != 1) return str();

                nint n = a[0].cast<nint>();
                return cast.substr(n, n + 1);
            }

        public:
            const params& getParams() const override {
                static params inner;
                if(inner.len() <= 0) {
                    inner.add(new param("index", new nInt()));
                }

                return inner;
            }
        };
    }

    NAMU(DEF_ME(nStr), DEF_VISIT())

    nbool me::nStrType::isImmutable() const { return true; }

    me::nStr() {}
    me::nStr(const nchar* val): super(std::string(val)) {}
    me::nStr(const std::string& val): super(val) {}

    dumScope* me::_onMakeSubs() const {
        static nStr inner;
        scope scapegoat;
        scapegoat.add(baseObj::CTOR_NAME, new defaultCtor(inner));
        scapegoat.add(baseObj::CTOR_NAME, new defaultCopyCtor(inner));

        scapegoat.add("len", new lenFunc());
        scapegoat.add("get", new getFunc());

        return new dumScope(scapegoat);
    }

    const ases& me::nStrType::_getAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            struct asBool : public tas<nBool> {
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
                        return str(new nBool(boolean));
                    } catch (std::invalid_argument& ex) {
                        return str();
                    }
                }
            };
            inner.add(new asBool());
            struct asFlt : public tas<nFlt> {
                str as(const node& me, const type& to) const override {
                    const std::string& val = me.cast<std::string>();
                    try {
                        nflt converted = stof(val);
                        return str(new nFlt(converted));
                    } catch (std::invalid_argument& ex) {
                        return str();
                    }
                }
            };
            inner.add(new asFlt());
            struct asInt: public tas<nInt> {
                str as(const node& me, const type& to) const override {
                    const std::string& val = me.cast<std::string>();
                    try {
                        nint converted = stoi(val);
                        return str(new nInt(converted));
                    } catch (std::invalid_argument& ex) {
                        return str();
                    }
                }
            };
            inner.add(new asInt());
            struct asChar : public tas<nChar> {
                str as(const node& me, const type& to) const override {
                    const std::string& val = me.cast<std::string>();
                    if (val.length() > 1) return str();

                    return str(new nChar(val.at(0)));
                }
            };
            inner.add(new asChar());
        }

        return inner;
    }
}
