#pragma once

#include "../../ast/Obj.hpp"

namespace wrd {

    template <typename T>
    class PrimitiveObj : public Obj {
        WRD_INTERFACE(PrimitiveObj, Obj)

    public:
        PrimitiveObj(): _val() {}
        PrimitiveObj(const T& val): _val(val) {}

        T& get() { return _val; }
        const T& get() const { return _val; }

    private:
        T _val;
    };
}
