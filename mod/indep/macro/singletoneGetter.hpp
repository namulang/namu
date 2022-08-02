#pragma once

#include "overload.hpp"

/// the macro for definining lazymethod which will be initialized when it's called.
//  this's uses static variable inside of method.
#define _SINGLETON_GETTER(SIGNATURE, StaticType, initValue) \
    SIGNATURE { \
        static StaticType inner initValue; \
        return inner; \
    }

#define NAMU_SINGLETON_GETTER_3(SIGNATURE, StaticType, initValue) \
    _SINGLETON_GETTER(SIGNATURE, StaticType, = initValue)

#define NAMU_SINGLETON_GETTER_2(SIGNATURE, StaticType) \
    _SINGLETON_GETTER(SIGNATURE, StaticType, NAMU_VOID())

#define NAMU_SINGLETON_GETTER_1(type) \
    _SINGLETON_GETTER(type& get(), type, NAMU_VOID())

#define NAMU_SINGLETON_GETTER(...)   NAMU_OVERLOAD(NAMU_SINGLETON_GETTER, __VA_ARGS__)
