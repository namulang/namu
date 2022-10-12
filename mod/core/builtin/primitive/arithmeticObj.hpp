#pragma once

#include "../../ast/scope.hpp"
#include "../../ast/baseObj.hpp"

namespace namu {

    class _nout arithmeticObj : public baseObj {
        NAMU(ADT(arithmeticObj, baseObj))

    public:
        const me& getOrigin() const override { return *this; }
        tstr<me> add(const me& rhs);
        tstr<me> sub(const me& rhs);
        tstr<me> mul(const me& rhs);
        tstr<me> div(const me& rhs);
        tstr<me> mod(const me& rhs);

    private:
        virtual tstr<me> _add(const me& rhs, nbool reversed) const = 0;
        virtual tstr<me> _sub(const me& rhs, nbool reversed) const = 0;
        virtual tstr<me> _mul(const me& rhs, nbool reversed) const = 0;
        virtual tstr<me> _div(const me& rhs, nbool reversed) const = 0;
        virtual tstr<me> _mod(const me& rhs, nbool reversed) const = 0;
    };
}
