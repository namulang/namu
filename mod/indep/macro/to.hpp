#pragma once

#include "../common/typedef.hpp"
#include "../helper/nulr.hpp"
#include "overload.hpp"
#include <vector>
#include <type_traits>

namespace nm {

    template <typename T> struct __empty__ {
        static T ret() { return T{}; }
    };

    template <typename T> struct __empty__<T&> {
        static T& ret() {
            T* ret = nullptr;
            return *ret;
        }
    };

    template <> struct __empty__<void> {
        static void ret() {}
    };

    template <typename T> struct __to_ref__ {
        static T to(T it) { return it; }
    };

    template <typename T> struct __to_ref__<T&> {
        static T& to(T& it) { return it; }
    };

    template <typename T> struct __to_ref__<const T&> {
        static const T& to(const T& it) { return it; }
    };

    template <typename T> struct __to_ref__<T*> {
        static T& to(T* it) { return *it; }
    };

    template <typename T> struct __to_ref__<T*&&> {
        static T& to(T*&& it) { return (T&) *it; }
    };

    template <typename T> struct __unwrap_binder__ {};

    template <typename T> struct __unwrap_binder__<T*> {
        static T* to(T* it) { return it; }
    };

    template <typename T> struct __unwrap_binder__<T&> {
        static T& to(T& it) { return it; }
    };

    template <typename T, typename F>
    auto operator->*(T* t, F&& f) -> decltype(f(__unwrap_binder__<decltype(t)>::to(t))) {
        return f(__unwrap_binder__<decltype(t)>::to(t));
    }

    template <typename T, typename F>
    auto operator->*(T& t, F&& f) -> decltype(f(__unwrap_binder__<decltype(t)>::to(t))) {
        return f(__unwrap_binder__<decltype(t)>::to(t));
    }

    template <typename T, typename F>
    auto operator->*(const T& t, F&& f) -> decltype(f(__unwrap_binder__<decltype(t)>::to(t))) {
        return f(__unwrap_binder__<decltype(t)>::to(t));
    }

    /// then is safe navigation feature of c++:
    /// usage:
    ///     as-is:
    ///     ```cpp
    ///         int getBrushColorCode(Resource r) {
    ///             auto& pallete = r.getPallete();
    ///             if(nul(pallete)) {
    ///                 log("pallete is null");
    ///                 return -1;
    ///             }
    ///
    ///             auto& canvas = pallete.getCanvas();
    ///             if(nul(canvas)) {
    ///                 log("canvas is null");
    ///                 return -1;
    ///             }
    ///
    ///             auto& brush = canvas.getBrush(BushType.SYSTEM);
    ///             if(nul(brush)) {
    ///                 log("brush is null");
    ///                 return -1;
    ///             }
    ///
    ///             return brush.getColorCode();
    ///         }
    ///     ```
    ///
    ///     to be:
    ///     ```cpp
    ///         int getBrushColorCode(Resource r) {
    ///             const int& code = r TO(getPallete()) TO(getCanvas()) TO(getBrush())
    ///             TO(getColorCode());
    ///             if(nul(code)) // if null returns during safe-navigation, output is nul
    ///             reference.
    ///                 return log("code is null"), -1;
    ///             return code;
    ///         }
    ///     ```
#define TO(fn)                                                                                \
    ->*[&](auto& __p) -> decltype(__to_ref__<decltype(__p)>::to(__p).fn) {                    \
        return !nul(__p) ? __to_ref__<decltype(__p)>::to(__p).fn :                            \
                           __empty__<decltype(__to_ref__<decltype(__p)>::to(__p).fn)>::ret(); \
    }

#define THEN_REF(fn)                                                                             \
    ->*[&](auto& __p) -> const decltype(__to_ref__<decltype(__p)>::to(__p).fn)& {                \
        return !nul(__p) ?                                                                       \
            __to_ref__<const typename std::remove_reference<decltype(__p)>::type&>::to(__p).fn : \
            __empty__<const decltype(__to_ref__<decltype(__p)>::to(__p).fn)&>::ret();            \
    }

} // namespace nm
