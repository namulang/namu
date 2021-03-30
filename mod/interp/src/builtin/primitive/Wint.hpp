#pragma once

#include "PrimitiveObj.hpp"

namespace wrd {

    class Wint : public PrimitiveObj<float> {

        class WintType : public TTypeBase<Wint, WType> {
            typedef TTypeBase<Wint, WType> _S;
            WRD_DECL_THIS(WintType, _S)

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

        WRD_CLASS(Wint, PrimitiveObj, WintType)

    public:
        Wint() {}
        Wint(const wint& val): Super(val) {}
    };
}
