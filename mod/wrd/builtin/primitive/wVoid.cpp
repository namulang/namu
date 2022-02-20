#include "wVoid.hpp"

namespace wrd {

    WRD_DEF_ME(wVoid)

    namespace {
        class wVoidCtor : public func {
            WRD(INTERFACE(wVoidCtor, func))

        public:
            wVoidCtor(): super("") {}

            const wtype& getEvalType() const override {
                return ttype<wVoid>::get();
            }
        };
        struct defaultCtor : public wVoidCtor {
            WRD(CLASS(defaultCtor, wVoidCtor))

        public:
            str _onCastArgs(narr& args) override {
                return str(new wVoid());
            }
        };
        struct cpyCtor: public wVoidCtor {
            WRD(CLASS(cpyCtor, wVoidCtor))

        public:
            str _onCastArgs(narr& args) override {
                return str(new wVoid());
            }
            const params& getParams() const override {
                static params* inner = nullptr;
                if(!inner) {
                    inner = new params();
                    inner->add(new ref(ttype<wVoid>::get()));
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
