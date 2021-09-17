#pragma once

#include "dep.hpp"

// wrdMeta macro's sub-commands:
//  CLONE:
//      defines normal clone func. it have to be defined if you
//      just have declared non abstract class.
#define __WRD__DECL_CLONE(ME) \
    public: \
        ME* clone() const override { \
            return new ME(*this); \
        } \
    private:

//  TYPE:
//      defines super meta type.
//      for instance, if you set TYPE(type), then when you call getType() of your class,
//      it will returns instance of type of type.
#define __WRD__DECL_TYPE(METATYPE) \
    public: \
        typedef METATYPE metaType; \
        const METATYPE& getType() const override { \
            return ttype<me>::get(); \
        } \
    private:

//  INIT META: it redirects to WRD_INIT_META macro.
#define __WRD__DECL_INIT_META(ME) WRD_INIT_META(ME)

// INTERFACE:
//      marks that this class is abstract.
#define __WRD__DECL_INTERFACE_1(ME) \
        __WRD__DECL_ME_1(ME) \
        __WRD__DECL_TYPE(wtype) \
        __WRD__DECL_INIT_META(ME)
#define __WRD__DECL_INTERFACE_2(ME, SUPER) \
        __WRD__DECL_INTERFACE_3(ME, SUPER, wtype)
#define __WRD__DECL_INTERFACE_3(ME, SUPER, SUPERTYPE) \
        __WRD__DECL_ME_2(ME, SUPER) \
        __WRD__DECL_TYPE(SUPERTYPE) \
        __WRD__DECL_INIT_META(ME)
#define __WRD__DECL_INTERFACE(...) WRD_OVERLOAD(__WRD__DECL_INTERFACE, __VA_ARGS__)

// CLASS:
//      marks that this class is concrete class.
#define __WRD__DECL_CLASS_1(ME) \
        __WRD__DECL_INTERFACE_1(ME) \
        __WRD__DECL_CLONE(ME)
#define __WRD__DECL_CLASS_2(ME, SUPER) \
        __WRD__DECL_INTERFACE_2(ME, SUPER) \
        __WRD__DECL_CLONE(ME)
#define __WRD__DECL_CLASS_3(ME, SUPER, SUPERTYPE) \
        __WRD__DECL_INTERFACE_3(ME, SUPER, SUPERTYPE) \
        __WRD__DECL_CLONE(ME)
#define __WRD__DECL_CLASS(...) WRD_OVERLOAD(__WRD__DECL_CLASS, __VA_ARGS__)
