#pragma once

#include "indep/common.hpp"
#include "indep/macro/namuMeta.hpp"
#include "indep/macro/declThis.hpp"
#include "indep/macro/unconstFunc.hpp"
#include "indep/helper/typeTrait.hpp"
#include <optional>

namespace nm {

    /// this is a wrapper class for std::optional.
    /// improved `optional`'s func name and signature because they are somewhat inconsistent
    /// from the perspective of namu and convention rules.
    /// as with std::optional, calling get() on an object that doesn't actually have a value
    /// will cause the app to crash.
    ///
    /// in namu, there are two cases where data must be returned with an error.
    ///     1. When returning by ref: use a binder such as tstr<T> or tweak<T>.
    ///     2. When returning by value: use tmay<T>.
    ///
    /// for details, refer to the return type rules of namu.
    template <typename T> class tmay: private std::optional<T> {
        NM(ME(tmay, std::optional<T>))

    public:
        tmay() = default;

        explicit tmay(const T& value);

    public:
        T* operator->();
        const T* operator->() const NM_CONST_FUNC(operator->());

        T& operator*();
        const T& operator*() const NM_CONST_FUNC(operator*());

        operator nbool() const;

    public:
        nbool has() const;

        T* get();
        const T* get() const NM_CONST_FUNC(get())

        virtual void rel();

        virtual void set(const T& arg);
    };

    // extension for OR macro:
    template <typename T, typename F> T& operator|(tmay<T>& t, F&& f) {
        f(t);
        // this may return null-reference but take it easy.
        // it'll never be used.
        return *t.get();
    }
    template <typename T, typename F> T& operator|(const tmay<T>& t, F&& f) {
        f(t);
        // this may return null-reference but take it easy.
        // it'll never be used.
        return *t.get();
    }
    template <typename T, typename F> T& operator|(tmay<T>&& t, F&& f) {
        f(t);
        // this may return null-reference but take it easy.
        // it'll never be used.
        return *t.get();
    }

    // extension for typeTrait:
    template <typename T> struct typeTrait<tmay<T>> {
        static nbool isNul(const tmay<T>& it) { return nul(&it) || !it.has(); }

        static constexpr nbool is_ptr = false;
        static constexpr nbool is_ref = false;
        static constexpr nbool is_like_ptr = true;
    };

    template <typename T> struct typeTrait<tmay<T>&> {
        static nbool isNul(const tmay<T>& it) { return !it.has(); }

        static constexpr nbool is_ptr = false;
        static constexpr nbool is_ref = true;
        static constexpr nbool is_like_ptr = true;
    };

    // extension for TO macro:
    template <typename T, typename F> auto operator->*(tmay<T>& t, F&& f) -> decltype(typeTrait<decltype(f(*t))>::ret()) {
        return t ? f(*t) : typeTrait<decltype(f(*t))>::ret();
    }

    template <typename T, typename F> auto operator->*(const tmay<T>& t, F&& f) -> decltype(typeTrait<decltype(f(*t))>::ret()) {
        return t ? f(*t) : typeTrait<decltype(f(*t))>::ret();
    }

    template <typename T, typename F> auto operator->*(tmay<T>&& t, F&& f) -> decltype(typeTrait<decltype(f(*t))>::ret()) {
        return t ? f(*t) : typeTrait<decltype(f(*t))>::ret();
    }

} // namespace nm
