#include "wInt.hpp"
#include "../../ast/param.hpp"

namespace wrd {

    WRD_DEF_ME(wInt)

    namespace {
        class wIntCtor : public func {
            WRD(ADT(wIntCtor, func))

        public:
            const wtype& getRetType() const override {
                return ttype<wInt>::get();
            }
        };
        struct defaultCtor : public wIntCtor {
            WRD(CLASS(defaultCtor, wIntCtor))

        public:
            str run(const ucontainable& args) override {
                return str(new wInt());
            }
            const params& getParams() const override {
                static params inner;
                return inner;
            }
        };
        struct cpyCtor: public wIntCtor {
            WRD(CLASS(cpyCtor, wIntCtor))

        public:
            str run(const ucontainable& args) override {
                int val = args.begin()->as<wInt>()->get();

                return str(new wInt(val));
            }
            const params& getParams() const override {
                static params* inner = nullptr;
                if(!inner) {
                    inner = new params();
                    inner->add(new param("", ttype<wInt>::get()));
                }
                return *inner;
            }
        };
    }

    void me::_onCreateCtors(tnarr<func>& tray) const {
        tray.add(new defaultCtor());
        tray.add(new cpyCtor());
    }

    wbool me::wIntType::isImmutable() const { return true; }

    const ases& me::wIntType::_getImpliAses() const {
        static ases inner;
        if(inner.len() <= 0) {
            struct toWstr: public tas<wStr> {
                str as(const node& wInt, const type& to) const override {
                    // TODO:
                    return str();
                }
            };
            inner.add(new toWstr());
        }

        return inner;
    }

    me::wInt() {}
    me::wInt(wint val): super(val) {}
}
