#pragma once

#include "primitiveObj.hpp"

namespace wrd {

    class wStr : public primitiveObj<std::string> {
        WRD(CLASS(wStr, primitiveObj, strType))

    public:
        wStr() {}
        wStr(const std::string& val): super(val) {}

    protected:
        void _onCreateCtors(funcs& tray) const override {
        }
            const ases& _getImpliAses() const override {
				static ases inner;
				if(inner.len() <= 0) {
					struct toWInt: public tas<wInt> {
						str as(const node& wStr, const type& to) const override {
							// TODO:
							return str();
						}
					};
					inner.add(new toWInt());
				}

				return inner;
            }
    };
}
