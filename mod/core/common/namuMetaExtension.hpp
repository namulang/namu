#pragma once

#include "dep.hpp"

// namuMeta macro's sub-commands:
//  CLONE:
//      defines normal clone func. it have to be defined if you
//      just have declared non abstract class.
#define __NAMU__DECL_CLONE(ME) \
    public: \
        ME* clone() const override { \
            return new ME(*this); \
        } \
    private:

//  TYPE:
//      defines super meta type.
//      for instance, if you set TYPE(type), then when you call getType() of your class,
//      it will returns instance of type of type.
#define __NAMU__DECL_TYPE(METATYPE) \
    public: \
        typedef METATYPE metaType; \
        const ntype& getType() const override { \
            return ttype<me>::get(); \
        } \
    private:

//  INIT META: it redirects to NAMU_INIT_META macro.
#define __NAMU__DECL_INIT_META(ME) NAMU_INIT_META(ME)

// INTERFACE:
//      marks that this class is abstract.
#define __NAMU__DECL_ADT_1(ME) \
        __NAMU__DECL_ME_1(ME) \
        __NAMU__DECL_TYPE(ntype) \
        __NAMU__DECL_INIT_META(ME)
#define __NAMU__DECL_ADT_2(ME, SUPER) \
        __NAMU__DECL_ADT_3(ME, SUPER, ntype)
#define __NAMU__DECL_ADT_3(ME, SUPER, SUPERTYPE) \
        __NAMU__DECL_ME_2(ME, SUPER) \
        __NAMU__DECL_TYPE(SUPERTYPE) \
        __NAMU__DECL_INIT_META(ME)
#define __NAMU__DECL_ADT(...) NAMU_OVERLOAD(__NAMU__DECL_ADT, __VA_ARGS__)

// CLASS:
//      marks that this class is concrete class.
#define __NAMU__DECL_CLASS_1(ME) \
        __NAMU__DECL_ADT_1(ME) \
        __NAMU__DECL_CLONE(ME)
#define __NAMU__DECL_CLASS_2(ME, SUPER) \
        __NAMU__DECL_ADT_2(ME, SUPER) \
        __NAMU__DECL_CLONE(ME)
#define __NAMU__DECL_CLASS_3(ME, SUPER, SUPERTYPE) \
        __NAMU__DECL_ADT_3(ME, SUPER, SUPERTYPE) \
        __NAMU__DECL_CLONE(ME)
#define __NAMU__DECL_CLASS(...) NAMU_OVERLOAD(__NAMU__DECL_CLASS, __VA_ARGS__)

// ACCEPT:
//      accept the visitor and let it can iterate sub elements.
//      please check 'visitor' class for more info.
#define __NAMU__DECL_VISIT_0() __NAMU__DECL_VISIT_1(super)
#define __NAMU__DECL_VISIT_1(SUPER) \
        public: \
            using SUPER::accept; \
            void accept(visitInfo i, visitor& v) override; \
        private:
#define __NAMU__DECL_VISIT(...) NAMU_OVERLOAD(__NAMU__DECL_VISIT, __VA_ARGS__)

#define __NAMU__DECL_DEF_VISIT_0() __NAMU__DECL_DEF_VISIT_1(me)
#define __NAMU__DECL_DEF_VISIT_1(ME) \
            void ME::accept(visitInfo i, visitor& v) { \
                v.visit(i, *this); \
            }
#define __NAMU__DECL_DEF_VISIT(...) NAMU_OVERLOAD(__NAMU__DECL_DEF_VISIT, __VA_ARGS__)

// VERIFY:
//      add new verification info to verify the type of specific object.
#define NAMU_VERIFY_NAME(name) __auto_verify_##name##__
#define NAMU_VERIFY_2(TYPE, BODY) \
    NAMU_INITIATOR(verification, { \
        typedef TYPE trait; \
        class NAMU_VERIFY_NAME(TYPE) : public tverification<TYPE> { \
        protected: \
            void _onVerify(trait& it) override BODY \
        }; \
        verifier::add(new NAMU_VERIFY_NAME(TYPE)()); \
    })
#define NAMU_VERIFY_1(BODY) NAMU_VERIFY_2(me, BODY)
#define NAMU_VERIFY_3(TYPE, NAME, BODY) \
    typedef TYPE trait; \
    class NAMU_VERIFY_NAME(TYPE##_##NAME) : public tverification<TYPE> { \
    protected: \
        void _onVerify(trait& it) override BODY \
    }; \
    NAMU_INITIATOR(verification, { \
        verifier::add(new NAMU_VERIFY_NAME(TYPE##_##NAME)()); \
    })
#define NAMU_VERIFY(...) NAMU_OVERLOAD(NAMU_VERIFY, __VA_ARGS__)

#define __NAMU__DECL_FRIEND_VERIFY(TYPE, NAME) friend class NAMU_VERIFY_NAME(TYPE##_##NAME);

#define __NAMU__DECL_VERIFY_3(TYPE, NAME, BODY) NAMU_VERIFY_3(TYPE, NAME, BODY)
#define __NAMU__DECL_VERIFY_2(TYPE, BODY) NAMU_VERIFY_2(TYPE, BODY)
#define __NAMU__DECL_VERIFY_1(BODY) NAMU_VERIFY_2(me, BODY)
#define __NAMU__DECL_VERIFY(...) NAMU_OVERLOAD(__NAMU__DECL_VERIFY, __VA_ARGS__)
