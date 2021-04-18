#pragma once

#include "primitiveObj.hpp"

namespace wrd {

    class fltObj : public primitiveObj<wflt> {

        class fltType : public ttypeBase<fltObj, wtype> {
            typedef ttypeBase<fltObj, wtype> _S;
            WRD_DECL_ME(fltType, _S)

        protected:
            const casts& _getImplis() const override {
                static casts* inner = nullptr;
                if(inner) return *inner;

                inner = new casts();
                struct toWstr: public cast {
                    const wtype& getType() const override {
                        // TODO:
                        return nulOf<wtype>();
                    }

                    ref as(const node& fltObj) const override {
                        // TODO:
                        return ref();
                    }
                };
                inner->push_back(new toWstr());

                return *inner;
            }
        };

        WRD_CLASS(fltObj, primitiveObj, fltType)

    public:
        fltObj() {}
        fltObj(const wflt& val): super(val) {}
    };


}
