#pragma once

#include "primitiveObj.hpp"

namespace wrd {

    class wStr : public primitiveObj<std::string> {

		class wStrType : public wtype {
		public:
			wbool isImmutable() const override { return true; }

		protected:
            const ases& _getImpliAses() const override;
		};
        WRD(CLASS(wStr, primitiveObj, wStrType))

    public:
        wStr() {}
        wStr(const std::string& val): super(val) {}

    protected:
        void _onCreateCtors(funcs& tray) const override {}
    };
}
