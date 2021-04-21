#pragma once

#include "primitiveObj.hpp"

namespace wrd {

    class intObj : public primitiveObj<wint> {

        class intType : public ttypeBase<intObj, wtype> {
            typedef ttypeBase<intObj, wtype> _S;
            WRD_DECL_ME(intType, _S)

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

                    ref as(const node& intObj) const override {
                        // TODO:
                        return ref();
                    }
                };
                inner->push_back(new toWstr());

                return *inner;
            }
        };

        WRD_CLASS(intObj, primitiveObj, intType)

    public:
        intObj() {}
        intObj(wint val): super(val) {}
    };
}
