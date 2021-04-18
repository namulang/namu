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

    private:
        T _val;
    };
}
