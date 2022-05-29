#include "wVoid.hpp"

namespace wrd {

    WRD_DEF_ME(wVoid)

    namespace {
        class wVoidCtor : public func {
            WRD(ADT(wVoidCtor, func))

        public:
            const wtype& getRetType() const override {
                return ttype<wVoid>::get();
            }
        };
        struct defaultCtor : public wVoidCtor {
            WRD(CLASS(defaultCtor, wVoidCtor))

        public:
            str run(const ucontainable& args) override {
                return str(new wVoid());
            }
        };
        struct cpyCtor: public wVoidCtor {
            WRD(CLASS(cpyCtor, wVoidCtor))

        public:
            str run(const ucontainable& args) override {
                return str(new wVoid());
            }
            const params& getParams() const override {
                static params* inner = nullptr;
                if(!inner) {
                    inner = new params();
                    inner->add(new param("", ttype<wVoid>::get()));
                }
                return *inner;
            }
        };
    }

    void me::_onCreateCtors(tnarr<func>& tray) const {
        tray.add(new defaultCtor());
        tray.add(new cpyCtor());
    }

    wbool me::wVoidType::isImmutable() const { return true; }

    const ases& me::wVoidType::_getImpliAses() const {
        static ases inner;
        return inner;
    }

    me::wVoid() {}

    funcs& me::getCtors() {
        static funcs* ctors = nullptr;
        if(!ctors) {
            ctors = new funcs();
            _onCreateCtors(*ctors);
        }

        return *ctors;
    }

    const obj& me::getOrigin() const {
        return *this;
    }

    me& me::singletone() {
        static me inner;
        return inner;
    }

    wbool me::_onSame(const typeProvidable& rhs) const {
        return !nul(rhs);
    }
}
