#pragma once

#include "PrimitiveObj.hpp"

namespace wrd {

    class WFlt : public PrimitiveObj<float> {

        class WFltType : public TTypeBase<WFlt, WType> {
            typedef TTypeBase<WFlt, WType> _S;
            WRD_DECL_THIS(WFltType, _S)

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

                    Ref as(const Node& fltObj) const override {
                        // TODO:
                        return Ref();
                    }
                };
                inner->push_back(new ToWstr());

                return *inner;
            }
        };

        WRD_CLASS(WFlt, PrimitiveObj, WFltType)

    public:
        WFlt() {}
        WFlt(const wflt& val): Super(val) {}
    };


}
