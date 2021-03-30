#pragma once

#include "PrimitiveObj.hpp"

namespace wrd {

    class WInt : public PrimitiveObj<float> {

        class WIntType : public TTypeBase<WInt, WType> {
            typedef TTypeBase<WInt, WType> _S;
            WRD_DECL_THIS(WIntType, _S)

        protected:
            const Ases& _getImplis() const override {
                static Ases* inner = nullptr;
                if(inner) return *inner;

                inner = new Ases();
                struct ToWstr: public As {
                    const WType& getType() const override {
                        // TODO:
                        return nulOf<WType>();
                    }

                    Ref as(const Node& intObj) const override {
                        // TODO:
                        return Ref();
                    }
                };
                inner->push_back(new ToWstr());

                return *inner;
            }
        };

        WRD_CLASS(WInt, PrimitiveObj, WIntType)

    public:
        WInt() {}
        WInt(const wint& val): Super(val) {}
    };
}
