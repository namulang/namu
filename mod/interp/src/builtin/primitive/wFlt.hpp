#pragma once

#include "primitiveObj.hpp"

namespace wrd {

    class wFlt : public primitiveObj<wflt> {

        class fltType : public ttypeBase<wFlt, wtype> {
            typedef ttypeBase<wFlt, wtype> _S;
            WRD_DECL_ME(fltType, _S)

        public:
            wbool isImmutable() const override {
                return true;
            }

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

                    ref as(const node& wFlt) const override {
                        // TODO:
                        return ref();
                    }
                };
                inner->push_back(new toWstr());

                return *inner;
            }
        };

        WRD_CLASS(wFlt, primitiveObj, fltType)

    public:
        wFlt() {}
        wFlt(wflt val): super(val) {}
    };


}
