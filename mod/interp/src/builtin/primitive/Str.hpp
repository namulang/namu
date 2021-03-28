#pragma once

#include "PrimitiveObj.hpp"

namespace wrd {

    class Str : public PrimitiveObj<std::string> {

        class TType<Str> : public TTypeBase<Str> {
            WRD_CLASS(StrType, WType)

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

        WRD_CLASS(Str, PrimitiveObj, StrType)

    public:
        Flt() {}
        Flt(const std::string& val): Super(val) {}
    };
}
