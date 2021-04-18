#pragma once

#include "primitiveObj.hpp"

namespace wrd {

    class strObj : public primitiveObj<std::string> {

        class strType : public ttypeBase<strObj, wtype> {
            typedef ttypeBase<strObj, wtype> _S;
            WRD_DECL_ME(strType, _S)

        protected:
            const casts& _getImplis() const override {
                static casts* inner = nullptr;
                if(inner) return *inner;

                inner = new casts();
                struct toWInt: public cast {
                    const wtype& getType() const override {
                        // TODO:
                        return nulOf<wtype>();
                    }
                    ref as(const node& strObj) const override {
                        // TODO:
                        return ref();
                    }
                };
                inner->push_back(new toWInt());

                return *inner;
            }
        };

        WRD_CLASS(strObj, primitiveObj, strType)

    public:
        strObj() {}
        strObj(const std::string& val): super(val) {}
    };
}
