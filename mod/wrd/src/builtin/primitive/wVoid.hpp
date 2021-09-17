#pragma once

#include "primitiveObj.hpp"

namespace wrd {

    class wVoid : public mgdObj {
        WRD(CLASS(wVoid, mgdObj, voidType))

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

		const ases& _getImpliAses() const override {
			static ases inner;
			if(inner.len() <= 0) {
				struct toStr: public tas<wStr>{
					str as(const node& wVoid, const type& to) const override {
						// TODO:
						return str();
					}
				};
				tray.push_back(new toStr());
			}
			return inner;
		}
    };
}
