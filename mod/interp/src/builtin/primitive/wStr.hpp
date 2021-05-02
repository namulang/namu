#pragma once

#include "primitiveObj.hpp"

namespace wrd {

    class wStr : public primitiveObj<std::string> {

        class strType : public ttypeBase<wStr, wtype> {
            typedef ttypeBase<wStr, wtype> _S;
            WRD_DECL_ME(strType, _S)

        public:
            wbool isImmutable() const override {
                return true;
            }

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
                    ref as(const node& wStr) const override {
                        // TODO:
                        return ref();
                    }
                };
                inner->push_back(new toWInt());

                return *inner;
            }
        };

        WRD_CLASS(wStr, primitiveObj, strType)

    public:
        wStr() {}
        wStr(const std::string& val): super(val) {}
    };
}
