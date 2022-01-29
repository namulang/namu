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
        const wtype& getType() const override { \
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

// VERIFY:
//		add new verification info to verify the type of specific object.
#define WRD_VERIFY_2(ME, BODY) \
	WRD_INITIATOR(verification, { \
		class __unnamed_verifi : public tverification<ME> { \
		protected: \
			wbool _onVerify(const ME& it) override BODY \
		}; \
        verifier::add(new __unnamed_verifi()); \
	})
#define WRD_VERIFY_1(BODY) WRD_VERIFY_2(me, BODY)
#define WRD_VERIFY(...) WRD_OVERLOAD(WRD_VERIFY, __VA_ARGS__)

#define __WRD__DECL_VERIFY_2(ME, BODY) WRD_VERIFY_2(ME, BODY)
#define __WRD__DECL_VERIFY_1(BODY) WRD_VERIFY_2(me, BODY)
#define __WRD__DECL_VERIFY(...) WRD_OVERLOAD(__WRD__DECL_VERIFY, __VA_ARGS__)
