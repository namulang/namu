#pragma once

#include "../common.hpp"

namespace namu {

    template <typename ... visitables>
    class visitor;

    template <typename traversable, typename T>
    class visitor<T> {
    protected:
        virtual void _onEnter(T& visitable) {}
        virtual void _onLeave(T& visitable) {}
        virtual void traverse(T& traversable) = 0;
    };

    template <typename T, typename... visitables>
    class visitor<T, visitables...> : public visitor<visitables....> {
    protected:
        using visitor<visitables....>::_onEnter;
        virtual void _onEnter(T& visitable) {}
        using visitor<visitables....>::_onLeave;
        virtual void _onLeave(T& visitable) {}
        using visitor<visitables....>::traverse;
        virtual void traverse(T& visitable) {}
    };
}

// namuMeta macro's sub-commands:
//  Classes that can be visited are broadly classified into two types.
//  one is the most basic type that can be traversed, and an API must be provided so that the
//  visitor can traverse from that type to another type.
//
//  The second one is derived types that can fire and catch events when visited.
//
#define __WRD__DECL_TRAVERSE_FOOTER \
        visitor._onEnter(*this); \
        visitor.traverse(*this); \
        visitor._onLeave(*this); \
    }

//  BASE_VISIT:
//      used this macro when it's the base type and at the same type it's the base type
//      that helps the visitor to traverse to another object.
#define __WRD__DECL_BASE_VISIT(VISITOR) \
    virtual void allowVisit(VISITOR& visitor) { \
        __WRD__DECL_TRAVERSE_FOOTER

//  VISIT:
//      this macro is used in the case of a derived type that a give class can visit.
#define __WRD__DECL_VISIT(VISITOR) \
    void allowVisit(VISITOR& visitor) override { \
        __WRD__DECL_TRAVERSE_FOOTER
