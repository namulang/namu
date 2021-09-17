#include "wVoid.hpp"
#include "../../ast/tref.hpp"

namespace wrd {

    WRD_DEF_ME(wVoid)

    namespace {
        class wVoidCtor : public primitiveCtor {
            WRD(INTERFACE(wVoidCtor, primitiveCtor))

        public:
            wVoidCtor(): super() {}

            const wtype& getReturnType() const override {
                return ttype<wVoid>::get();
            }
        };
        struct defaultCtor : public wVoidCtor {
            WRD(CLASS(defaultCtor, wVoidCtor))

        public:
            str _onCast(narr& args) override {
                return str(new wVoid());
            }
            const types& getTypes() const override {
                static types inner;
                return inner;
            }
        };
        struct cpyCtor: public wVoidCtor {
            WRD(CLASS(cpyCtor, wVoidCtor))

        public:
            str _onCast(narr& args) override {
                return str(new wVoid());
            }
            const types& getTypes() const override {
                static types* inner = nullptr;
                if(!inner) {
                    inner = new types();
                    inner->push_back(&ttype<wVoid>::get());
                }
                return *inner;
            }
        };
    }

    void me::_onCreateCtors(tnarr<func>& tray) const {
        tray.add(new defaultCtor());
        tray.add(new cpyCtor());
    }
}
