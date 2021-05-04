#include "wInt.hpp"
#include "../../ast/tref.hpp"

namespace wrd {

    WRD_DEF_ME(wInt)

    namespace {
        class wIntCtor : public func {
            WRD_INTERFACE(wIntCtor, func)

        public:
            wIntCtor(): super("") {}

            const wtype& getReturnType() const override {
                return ttype<wInt>::get();
            }
        };
        struct defaultCtor : public wIntCtor {
            WRD_CLASS(defaultCtor, wIntCtor)

        public:
            str _onRun(ncontainer& args) override {
                return str(new wInt());
            }
        };
        struct intCtor : public wIntCtor {
            WRD_CLASS(intCtor, wIntCtor)

        public:
            str _onRun(ncontainer& args) override {
                int val = args.begin()->as<wInt>()->get();

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
        tray.add(new intCtor());
    }
}
