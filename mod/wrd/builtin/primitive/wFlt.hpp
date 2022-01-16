#pragma once

#include "wStr.hpp"

namespace wrd {

    class wFlt : public primitiveObj<wflt> {

		class wFltType : public wtype {
		public:
			wbool isImmutable() const override { return true; }

		protected:
			const ases& _getImpliAses() const override {
				static ases inner;
				if(inner.len() <= 0) {
					struct toWstr: public tas<wStr> {
						str as(const node& wFlt, const type& to) const override {
							// TODO:
							return str();
						}
					};
					inner.add(new toWstr());
				}

				return inner;
			}
		};
        WRD(CLASS(wFlt, primitiveObj, wFltType))

    public:
        wFlt() {}
        wFlt(wflt val): super(val) {}

    protected:
        void _onCreateCtors(funcs& tray) const override {}
    };

}
