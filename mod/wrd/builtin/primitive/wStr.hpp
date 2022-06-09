#pragma once

#include "primitiveObj.hpp"

namespace wrd {

    class _wout wStr : public primitiveObj<std::string> {

        class _wout wStrType : public wtype {
        public:
            wbool isImmutable() const override;

        protected:
            const ases& _getImpliAses() const override;
        };
        WRD(CLASS(wStr, primitiveObj, wStrType))

    public:
        wStr();
        wStr(const wchar* val);
        wStr(const std::string& val);

    protected:
        dumScope* _onMakeCtors() const override;
    };
}
