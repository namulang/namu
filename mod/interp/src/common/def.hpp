#pragma once

#include "dep.hpp"

namespace wrd {

#define _WRD_INTERFACE_FOOTER(THIS) \
        WRD_INIT_META(THIS) \
    public: \
        typedef WType SuperType; \
        const Type& getType() const override { \
            return TType<This>::get(); \
        } \
    private:

#define WRD_CLONE(THIS) \
    public: \
        THIS* clone() const override { \
            return new THIS(*this); \
        } \
    private:

#define WRD_INTERFACE_1(THIS) \
        WRD_DECL_THIS_1(THIS) \
        _WRD_INTERFACE_FOOTER(THIS)
#define WRD_INTERFACE_2(THIS, SUPER) \
        WRD_DECL_THIS_2(THIS, SUPER) \
        _WRD_INTERFACE_FOOTER(THIS)
#define WRD_INTERFACE(...) WRD_OVERLOAD(WRD_INTERFACE, __VA_ARGS__)

#define WRD_CLASS_1(THIS) \
        WRD_INTERFACE_1(THIS) \
        WRD_CLONE(THIS)
#define WRD_CLASS_2(THIS, SUPER) \
        WRD_INTERFACE_2(THIS, SUPER) \
        WRD_CLONE(THIS)
#define WRD_CLASS(...) WRD_OVERLOAD(WRD_CLASS, __VA_ARGS__)

    class Node;
    typedef TStr<Node> Str;
    typedef TWeak<Node> Weak;
}
