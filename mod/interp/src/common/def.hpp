#pragma once

#include "dep.hpp"

namespace wrd {

#define WRD_INTERFACE_FOOTER(ME, SUPERTYPE) \
    public: \
        typedef SUPERTYPE SuperType; \
        const SuperType& getType() const override { \
            return TType<me>::get(); \
        } \
        WRD_INIT_META(ME) \
    private:

#define WRD_CLONE(ME) \
    public: \
        ME* clone() const override { \
            return new ME(*this); \
        } \
    private:

#define WRD_INTERFACE_1(ME) \
        WRD_DECL_ME_1(ME) \
        WRD_INTERFACE_FOOTER(ME, WType)
#define WRD_INTERFACE_2(ME, SUPER) \
        WRD_INTERFACE_3(ME, SUPER, WType)
#define WRD_INTERFACE_3(ME, SUPER, SUPERTYPE) \
        WRD_DECL_ME_2(ME, SUPER) \
        WRD_INTERFACE_FOOTER(ME, SUPERTYPE)
#define WRD_INTERFACE(...) WRD_OVERLOAD(WRD_INTERFACE, __VA_ARGS__)

#define WRD_CLASS_1(ME) \
        WRD_INTERFACE_1(ME) \
        WRD_CLONE(ME)
#define WRD_CLASS_2(ME, SUPER) \
        WRD_INTERFACE_2(ME, SUPER) \
        WRD_CLONE(ME)
#define WRD_CLASS_3(ME, SUPER, SUPERTYPE) \
        WRD_INTERFACE_3(ME, SUPER, SUPERTYPE) \
        WRD_CLONE(ME)
#define WRD_CLASS(...) WRD_OVERLOAD(WRD_CLASS, __VA_ARGS__)

    class Node;
    class WType;
    typedef TStr<Node> Str;
    typedef TWeak<Node> Weak;
}
