#pragma once

#include "ttypeBase.hpp"

namespace namu {

    /// @remark TType returns TType<Type> as its meta class.
    ///         however, this makes impossible to get specific TType instance
    ///         at a binder.
    ///
    ///         if user typedefs SuperType at their type T, then TType
    ///         inherits from given SuperType.
    ///         this eventually make user add API to want to TType class.
    template<typename T>
    class ttype : public ttypeBase<T> {};
}
