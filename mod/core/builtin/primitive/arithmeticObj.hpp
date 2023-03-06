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

        nbool eq(const me& rhs) const;
        nbool ne(const me& rhs) const;
        nbool gt(const me& rhs) const;
        nbool lt(const me& rhs) const;
        nbool ge(const me& rhs) const;
        nbool le(const me& rhs) const;
        nbool logicalAnd(const me& rhs) const;
        nbool logicalOr(const me& rhs) const;

        /// same to 'assign'.
        tstr<me> mov(const me& rhs);

    private:
        virtual tstr<me> _add(const me& rhs, nbool reversed) const = 0;
        virtual tstr<me> _sub(const me& rhs, nbool reversed) const = 0;
        virtual tstr<me> _mul(const me& rhs, nbool reversed) const = 0;
        virtual tstr<me> _div(const me& rhs, nbool reversed) const = 0;
        virtual tstr<me> _mod(const me& rhs, nbool reversed) const = 0;

        virtual nbool _eq(const me& rhs) const = 0;
        virtual nbool _ne(const me& rhs) const = 0;
        virtual nbool _gt(const me& rhs) const = 0;
        virtual nbool _lt(const me& rhs) const = 0;
        virtual nbool _ge(const me& rhs) const = 0;
        virtual nbool _le(const me& rhs) const = 0;
        virtual nbool _logicalAnd(const me& rhs) const = 0;
        virtual nbool _logicalOr(const me& rhs) const = 0;

        virtual me& _mov(const me& rhs) = 0;
    };
}
