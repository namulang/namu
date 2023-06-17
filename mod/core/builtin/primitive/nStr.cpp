#include "nStr.hpp"
#include "../../ast/defaultCtor.hpp"
#include "../../ast/defaultCopyCtor.hpp"
#include "nBool.hpp"
#include "nInt.hpp"
#include "nFlt.hpp"
#include "nChar.hpp"
#include "nByte.hpp"
#include "../../visitor/visitor.hpp"
#include "../container/mgd/seq.hpp"

namespace namu {

    namespace {
        class lenFunc : public APIBridge<nStr, nInt> {
            typedef APIBridge<nStr, nInt> __super__;
            NAMU(CLASS(lenFunc, __super__))

        protected:
            str _onRun(nStr& cast, const args& a) const override {
                return new nInt(cast.len());
            }
        };

        class getFunc : public APIBridge<nStr, nChar> {
            typedef APIBridge<nStr, nStr> __super__;
            NAMU(CLASS(getFunc, __super__))

        protected:
            str _onRun(nStr& cast, const args& a) const override {
                if(a.len() != 1) return str();

                nint n = a[0].cast<nint>();
                return new nChar(cast[n]);
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

        class getSeqFunc : public APIBridge<nStr, nStr> {
            typedef APIBridge<nStr, nStr> __super__;
            NAMU(CLASS(getSeqFunc, __super__))

        protected:
            str _onRun(nStr& cast, const args& a) const override {
                if(a.len() != 1) return str();

                tstr<seq> s = a[0].as<seq>();
                if(!s) return str();

                nint start = (*s)[0];
                nint end = (*s)[s->len()-1] + 1;
                return cast.substr(start, end);
            }

        public:
            const params& getParams() const override {
                static params inner;
                if(inner.len() <= 0) {
                    inner.add(new param("index", new seq(0, 1)));
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

    void me::_onMakeSubs(scope& tray) const {
        static nStr inner;
        tray.add(baseObj::CTOR_NAME, new defaultCtor(inner));
        tray.add(baseObj::CTOR_NAME, new defaultCopyCtor(inner));
        tray.add("len", new lenFunc());
        tray.add("get", new getFunc());
        tray.add("get", new getSeqFunc());
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
                            boolean = stoi(val, nullptr, 0) == 0;
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
                        nint converted = stoi(val, nullptr, 0);
                        return str(new nInt(converted));
                    } catch (std::invalid_argument& ex) {
                        return str();
                    }
                }
            };
            inner.add(new asInt());
            struct asByte : public tas<nByte> {
                str as(const node& me, const type& to) const override {
                    const std::string& val = me.cast<std::string>();
                    if(val.length() <= 0) return str();

                    return new nByte(val[0]);
                }
            };
            inner.add(new asByte());
            struct asChar : public tas<nChar> {
                str as(const node& me, const type& to) const override {
                    const std::string& val = me.cast<std::string>();
                    if(val.length() <= 0) return str();

                    return new nChar(val[0]);
                }
            };
            inner.add(new asChar());
        }

        return inner;
    }
}
