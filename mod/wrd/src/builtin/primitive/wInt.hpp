#pragma once

#include "primitiveObj.hpp"

namespace wrd {

    class wInt : public primitiveObj<wint> {
        WRD(CLASS(wInt, primitiveObj))

    public:
        wInt() {}
        wInt(wint val): super(val) {}

    protected:
        void _onCreateCtors(funcs& tray) const override;
		const ases& _getImpliAses() const override {
			static ases inner;
			if(inner.len() <= 0) {
                struct toWstr: public tas<wStr> {
                    str as(const node& wInt, const type& to) const override {
                        // TODO:
                        return str();
                    }
                };
                inner.add(new toWstr());
			}

			return inner;
		}
    };
}
