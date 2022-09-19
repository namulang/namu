#pragma once

#include "dep.hpp"

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
