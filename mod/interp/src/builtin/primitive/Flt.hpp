#pragma once

#include "PrimitiveObj.hpp"

namespace wrd {

    class Flt : public PrimitiveObj<float> {

        class TType<Flt> : public TTypeBase<Flt> {
            WRD_CLASS(FltType, WType)

        protected:
            const Ases& _getImplis() const override {
                static Ases* inner = nullptr;
                if(nul(inner)) {
                    inner = new Ases();

                    struct ToStr: public Asable {
                        wbool is(const Type& type) const override {
                            // TODO:
                            return false;
                        }

                        Ref as(const TypeProvidable& it) const override {
                            // TODO:
                            return Ref();
                        }
                    };
                    inner->push_back(new ToStr());
                }
            }
        };

        WRD_CLASS(Flt, PrimitiveObj, FltType)

    public:
        Flt() {}
        Flt(const wflt& val): Super(val) {}
    };
}
