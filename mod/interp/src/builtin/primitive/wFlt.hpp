#pragma once

#include "primitiveObj.hpp"

namespace wrd {

    class wFlt : public primitiveObj<wflt> {

        class fltType : public primitiveType {
            WRD_DECL_ME(fltType, primitiveType)

        protected:
            void _onCreateImplis(casts& tray) const override {
                struct toWstr: public cast {
                    const wtype& getType() const override {
                        // TODO:
                        return nulOf<wtype>();
                    }

                    ref as(const node& wFlt) const override {
                        // TODO:
                        return ref();
                    }
                };
                tray.push_back(new toWstr());
            }
        };

        WRD_CLASS(wFlt, primitiveObj, fltType)

    public:
        wFlt() {}
        wFlt(wflt val): super(val) {}

    protected:
        void _onCreateCtors(funcs& tray) const override {
        }
    };

}
