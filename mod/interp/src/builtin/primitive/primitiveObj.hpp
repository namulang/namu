#pragma once

#include "../../ast/obj.hpp"

namespace wrd {

    template <typename T>
    class primitiveObj : public obj {
        WRD_INTERFACE(primitiveObj, obj)

    public:
        primitiveObj(): _val() {}
        primitiveObj(const T& val): _val(val) {}

        T& get() { return _val; }
        const T& get() const { return _val; }

    protected:
        wbool _onSame(const typeProvidable& rhs) const override {
            const me& cast = (const me&) rhs;
            return _val == cast._val;
        }

    private:
        T _val;
    };
}
