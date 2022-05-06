#include "wVoid.hpp"

namespace wrd {

    WRD_DEF_ME(wVoid)

    namespace {
        class wVoidCtor : public func {
            WRD(INTERFACE(wVoidCtor, func))

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
}
