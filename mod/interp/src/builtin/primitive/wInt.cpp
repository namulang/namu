#include "wInt.hpp"
#include "../../ast/tref.hpp"

namespace wrd {

    WRD_DEF_ME(wInt)

    namespace {
        class wIntCtor : public primitiveCtor {
            WRD(INTERFACE(wIntCtor, primitiveCtor))

        public:
            wIntCtor(): super() {}

            const wtype& getReturnType() const override {
                return ttype<wInt>::get();
            }
        };
        struct defaultCtor : public wIntCtor {
            WRD(CLASS(defaultCtor, wIntCtor))

        public:
            str _onCast(narr& args) override {
                return str(new wInt());
            }
            const wtypes& getTypes() const override {
                static wtypes inner;
                return inner;
            }
        };
        struct cpyCtor: public wIntCtor {
            WRD(CLASS(cpyCtor, wIntCtor))

        public:
            str _onCast(narr& args) override {
                int val = args[0].as<wInt>()->get();

                return str(new wInt(val));
            }
            const wtypes& getTypes() const override {
                static wtypes* inner = nullptr;
                if(!inner) {
                    inner = new wtypes();
                    inner->push_back(&ttype<wInt>::get());
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
