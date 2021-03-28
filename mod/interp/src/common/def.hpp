#pragma once

#include "dep.hpp"

namespace wrd {

#define WRD_INTERFACE_FOOTER(THIS, SUPERTYPE) \
    public: \
        typedef SUPERTYPE SuperType; \
        const SuperType& getType() const override { \
            return TType<This>::get(); \
        } \
        WRD_INIT_META(THIS) \
    private:

#define WRD_CLONE(THIS) \
    public: \
        THIS* clone() const override { \
            return new THIS(*this); \
        } \
    private:

#define WRD_INTERFACE_1(THIS) \
        WRD_DECL_THIS_1(THIS) \
        WRD_INTERFACE_FOOTER(THIS, WType)
#define WRD_INTERFACE_2(THIS, SUPER) \
        WRD_INTERFACE_3(THIS, SUPER, WType)
#define WRD_INTERFACE_3(THIS, SUPER, SUPERTYPE) \
        WRD_DECL_THIS_2(THIS, SUPER) \
        WRD_INTERFACE_FOOTER(THIS, SUPERTYPE)
#define WRD_INTERFACE(...) WRD_OVERLOAD(WRD_INTERFACE, __VA_ARGS__)

#define WRD_CLASS_1(THIS) \
        WRD_INTERFACE_1(THIS) \
        WRD_CLONE(THIS)
#define WRD_CLASS_2(THIS, SUPER) \
        WRD_INTERFACE_2(THIS, SUPER) \
        WRD_CLONE(THIS)
#define WRD_CLASS_3(THIS, SUPER, SUPERTYPE) \
        WRD_INTERFACE_3(THIS, SUPER, SUPERTYPE) \
        WRD_CLONE(THIS)
#define WRD_CLASS(...) WRD_OVERLOAD(WRD_CLASS, __VA_ARGS__)

    class Node;
    class WType;
    typedef TStr<Node> Str;
    typedef TWeak<Node> Weak;
}
