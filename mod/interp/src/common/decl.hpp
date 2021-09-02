#pragma once

#include "dep.hpp"

namespace wrd {


    // world universal DECL macro:
    //  WRD_DECL is generalized API used to describe the metadata of
    //  class in wrd.
    //  WRD_DECL can be used to define detailed metadata about a class by chaining sub-command sets.
    //  with WRD macro, I can clarify that those INIT_META, VISIT are should be after of WRD macro.
    //  and limit the scope of availbility.
    //  these macros which are available only inside of WRD macro are called to sub-commands.
    //
    // Usage:
    //  use WRD_DECL macro at declaration of your class.
    //
    //  class Foo {
    //      WRD_DECL(cmd1(arg1, arg2, ...), cmd2(arg1, arg2, ...), ...)
    //
    //  public:
    //      ...and your codes...
    //  };
#define _ON_EACH_DECL(cmd) __WRD__DECL_##cmd
#define WRD(...) WRD_EACH(_ON_EACH_DECL, __VA_ARGS__)

    // sub-commands:
    //  ME: actually it redirects builtin macro 'WRD_DECL_ME'.
#define __WRD__DECL_ME_1(ME) WRD_DECL_ME_1(ME)
#define __WRD__DECL_ME_2(ME, SUPER) WRD_DECL_ME_2(ME, SUPER)
#define __WRD__DECL_ME(...) WRD_OVERLOAD(__WRD__DECL_ME, __VA_ARGS__)

    //  CLONE:
    //      defines normal clone func. it have to be defined if you
    //      just have declared non abstract class.
#define __WRD__DECL_CLONE(ME) \
    public: \
        ME* clone() const override { \
            return new ME(*this); \
        } \
    private:

    //  META_TYE:
    //      defines super meta type.
    //      for instance, if you set META_TYPE(wtype), then when you call getType() of your class,
    //      it will returns instance of type of wtype.
#define __WRD__DECL_META_TYPE(METATYPE) \
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
        __WRD__DECL_META_TYPE(wtype) \
        __WRD__DECL_INIT_META(ME)
#define __WRD__DECL_INTERFACE_2(ME, SUPER) \
        __WRD__DECL_INTERFACE_3(ME, SUPER, wtype)
#define __WRD__DECL_INTERFACE_3(ME, SUPER, SUPERTYPE) \
        __WRD__DECL_ME_2(ME, SUPER) \
        __WRD__DECL_META_TYPE(SUPERTYPE) \
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
}
