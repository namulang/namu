#pragma once

#include "PrimitiveObj.hpp"

namespace wrd {

    class Wstr : public PrimitiveObj<std::string> {

        class WstrType : public TTypeBase<Wstr, WType> {
            typedef TTypeBase<Wstr, WType> _S;
            WRD_DECL_THIS(WstrType, _S)

        protected:
            const Ases& _getImplis() const override {
                static Ases* inner = nullptr;
                if(inner) return *inner;

                inner = new Ases();
                struct ToWint: public As {
                    const WType& getType() const override {
                        // TODO:
                        return nulOf<WType>();
                    }
                    Ref as(const Node& strObj) const override {
                        // TODO:
                        return Ref();
                    }
                };
                inner->push_back(new ToWint());

                return *inner;
            }
        };

        WRD_CLASS(Wstr, PrimitiveObj, WstrType)

    public:
        Wstr() {}
        Wstr(const std::string& val): Super(val) {}
    };
}
