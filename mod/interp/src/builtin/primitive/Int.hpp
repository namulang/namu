#pragma once

#include "PrimitiveObj.hpp"

namespace wrd {

    class Int : public PrimitiveObj<float> {

        class TType<Int> : public TTypeBase<Int> {
            WRD_CLASS(IntType, WType)

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

        WRD_CLASS(Int, PrimitiveObj, IntType)

    public:
        Int() {}
        Int(const wint& val): Super(val) {}
    };
}
