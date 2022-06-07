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

    public:
        using super::subs;
        nbicontainer& subs() override {
            static scope* inner = nullptr;
            if(nul(inner))
                _onMakeCtors(*(inner = new scope()));

            return *inner;
        }

    protected:
        void _onMakeCtors(scope& tray) const override;

    };
}
