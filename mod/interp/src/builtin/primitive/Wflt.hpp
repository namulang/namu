#pragma once

#include "PrimitiveObj.hpp"

namespace wrd {

    class Wflt : public PrimitiveObj<float> {

        class WfltType : public TTypeBase<Wflt, WType> {
            typedef TTypeBase<Wflt, WType> _S;
            WRD_DECL_THIS(WfltType, _S)

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

        WRD_CLASS(Wflt, PrimitiveObj, WfltType)

    public:
        Wflt() {}
        Wflt(const wflt& val): Super(val) {}
    };


}
