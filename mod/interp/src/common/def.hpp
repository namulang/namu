#pragma once

#include "dep.hpp"

#define _WRD_CLASS_FOOTER(THIS) \
    WRD_INIT_META(THIS) \
public: \
    typedef SuperType WType; \
    virtual Type& getType() const { \
        return TType<This>::get(); \
    } \
    WRD_CLONE(THIS) \
private:

#define WRD_CLONE(THIS) \
public: \
    TStr<THIS> clone() { \
        return new THIS(*this); \
    } \
private:

#define WRD_CLASS_1(THIS) \
    WRD_DECL_THIS_1(THIS) \
    _WRD_CLASS_FOOTER(THIS)

#define WRD_CLASS_2(THIS, SUPER) \
    WRD_DECL_THIS_2(THIS, SUPER) \
    _WRD_CLASS_FOOTER(THIS)

#define WRD_CLASS(...) WRD_OVERLOAD(WRD_CLASS, __VA_ARGS__)
