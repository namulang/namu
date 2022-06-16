#pragma once

#include "../../ast/mgd.hpp"
#include "../../ast/scope.hpp"

namespace wrd {

    class arithmeticObj : public obj {
        WRD(ADT(arithmeticObj, obj))

    public:
        const obj& getOrigin() const override { return *this; }
        tstr<arithmeticObj> add(const arithmeticObj& rhs);
        tstr<arithmeticObj> sub(const arithmeticObj& rhs);
        tstr<arithmeticObj> mul(const arithmeticObj& rhs);
        tstr<arithmeticObj> div(const arithmeticObj& rhs);
        tstr<arithmeticObj> mod(const arithmeticObj& rhs);

    private:
        virtual tstr<arithmeticObj> _add(const arithmeticObj& rhs) const = 0;
        virtual tstr<arithmeticObj> _sub(const arithmeticObj& rhs) const = 0;
        virtual tstr<arithmeticObj> _mul(const arithmeticObj& rhs) const = 0;
        virtual tstr<arithmeticObj> _div(const arithmeticObj& rhs) const = 0;
        virtual tstr<arithmeticObj> _mod(const arithmeticObj& rhs) const = 0;
    };
}
