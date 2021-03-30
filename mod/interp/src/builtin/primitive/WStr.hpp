#pragma once

#include "PrimitiveObj.hpp"

namespace wrd {

    class WStr : public PrimitiveObj<std::string> {

        class WStrType : public TTypeBase<WStr, WType> {
            typedef TTypeBase<WStr, WType> _S;
            WRD_DECL_THIS(WStrType, _S)

        protected:
            const Ases& _getImplis() const override {
                static Ases* inner = nullptr;
                if(inner) return *inner;

                inner = new Ases();
                struct ToWInt: public As {
                    const WType& getType() const override {
                        // TODO:
                        return nulOf<WType>();
                    }
                    Ref as(const Node& strObj) const override {
                        // TODO:
                        return Ref();
                    }
                };
                inner->push_back(new ToWInt());

                return *inner;
            }
        };

        WRD_CLASS(WStr, PrimitiveObj, WStrType)

    public:
        WStr() {}
        WStr(const std::string& val): Super(val) {}
    };
}
