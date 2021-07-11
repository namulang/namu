#pragma once

#include "primitiveObj.hpp"
#include "../../ast/ref.hpp"

namespace wrd {

    class wVoid : public mgdObj {

        class voidType : public primitiveType {
            WRD_DECL_ME(voidType, primitiveType)

        protected:
            void _onCreateImplis(casts& tray) const override {
                struct toWstr: public cast {
                    const wtype& getType() const override {
                        // TODO:
                        return nulOf<wtype>();
                    }

                    ref as(const node& wVoid) const override {
                        // TODO:
                        return ref();
                    }
                };
                tray.push_back(new toWstr());
            }
        };

        WRD_CLASS(wVoid, mgdObj, voidType)

    public:
        wVoid() {}

    public:
        using super::getCtors;
        funcs& getCtors() override {
            static funcs* ctors = nullptr;
            if(!ctors) {
                ctors = new funcs();
                _onCreateCtors(*ctors);
            }

            return *ctors;
        }

        const obj& getOrigin() const override {
            return *this;
        }

    protected:
        wbool _onSame(const typeProvidable& rhs) const override {
            return !nul(rhs);
        }

        void _onCreateCtors(funcs& tray) const;
    };
}
