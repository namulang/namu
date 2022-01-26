#include "wInt.hpp"

namespace wrd {

    WRD_DEF_ME(wInt)

    namespace {
        class wIntCtor : public func {
            WRD(INTERFACE(wIntCtor, func))

        public:
            wIntCtor(): super("") {}

            const wtype& getEvalType() const override {
                return ttype<wInt>::get();
            }
        };
        struct defaultCtor : public wIntCtor {
            WRD(CLASS(defaultCtor, wIntCtor))

        public:
            str _onCast(narr& args) override {
                return str(new wInt());
            }
            const wtypes& getParams() const override {
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
            const wtypes& getParams() const override {
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
