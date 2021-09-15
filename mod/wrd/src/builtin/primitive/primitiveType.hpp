#pragma once

#include "../../type/wtype.hpp"

namespace wrd {

    class primitiveType : public wtype {
        WRD_DECL_ME(primitiveType, wtype)

    public:
        wbool isImmutable() const override {
            return true;
        }

    protected:
        const casts& _getImplis() const override {
            static casts* inner = nullptr;
            if(inner) return *inner;

            inner = new casts();
            _onCreateImplis(*inner);

            return *inner;
        }
        virtual void _onCreateImplis(casts& tray) const = 0;
    };
}

