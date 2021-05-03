#pragma once

#include "primitiveObj.hpp"

namespace wrd {

    class wInt : public primitiveObj<wint> {

        class intType : public primitiveType {
            WRD_DECL_ME(intType, primitiveType)

        protected:
            void _onCreateImplis(casts& tray) const override {
                struct toWstr: public cast {
                    const wtype& getType() const override {
                        // TODO:
                        return nulOf<wtype>();
                    }

                    ref as(const node& wInt) const override {
                        // TODO:
                        return ref();
                    }
                };
                tray.push_back(new toWstr());
            }
        };

        WRD_CLASS(wInt, primitiveObj, intType)

    public:
        wInt() {}
        wInt(wint val): super(val) {}

    protected:
        void _onCreateCtors(tnarr<func>& tray) const override {
        }
    };
}
