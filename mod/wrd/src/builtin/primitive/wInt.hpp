#pragma once

#include "wStr.hpp"

namespace wrd {

    class wInt : public primitiveObj<wint> {

		class wIntType : public wtype {
		public:
			wbool isImmutable() const override { return true; }

		protected:
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
        WRD(CLASS(wInt, primitiveObj, wIntType))

    public:
        wInt() {}
        wInt(wint val): super(val) {}

    protected:
        void _onCreateCtors(funcs& tray) const override;
    };
}
