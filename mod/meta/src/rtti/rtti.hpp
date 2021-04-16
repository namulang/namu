#pragma once

#include "../common.hpp"
#include "./type/adam.hpp"

namespace wrd {

    class metaIf {
    protected:
        typedef short yes;
        typedef char no;
    };

    template <typename T>
    struct tifTemplate : public metaIf {
        template <template<typename> class Template, typename X>
        static yes _foo(Template<X>*);
        static no _foo(...);

        static inline constexpr wbool is = sizeof(_foo((T*)0)) == sizeof(yes);
    };

    template <typename T, typename super> // is T is sub of super
    struct tifSub {
        static inline constexpr wbool is = std::is_base_of<super, T>::value;
    };

    template <typename T>
    struct taEmptyCan {
        typedef void is;
    };
    template <typename T, typename = void>
    struct tifHasSuperTypedef : public metaIf {
        static inline constexpr wbool is = false;
    };
    template <typename T>
    struct tifHasSuperTypedef<T, typename taEmptyCan<typename T::super>::is> : public metaIf {
        static inline constexpr wbool is = true;
    };

    template <typename T, wbool typedefsuper = tifHasSuperTypedef<T>::is>
    struct tadaptiveSuper : metaIf {
        typedef adam super;
    };
    template <typename T>
    struct tadaptiveSuper<T, true> {
        typedef typename T::super super;
    };

    template <typename T, wbool canMake = std::is_constructible<T>::value>
    struct tinstanceMaker {
        static void* make() { return nullptr; }
    };
    template <typename T>
    struct tinstanceMaker<T, true> {
        static void* make() { return new T(); }
    };

    struct nameDemangler {
        static std::string demangle(const wchar* org) {
            wchar* demangled = nullptr;
            int status = 0;

            demangled = ::abi::__cxa_demangle(org, 0, 0, &status);
            std::string ret(demangled);

            free(demangled);
            return ret;
        }
    };

    /// @remark TClass is a class template using monostate pattern.
    ///         so it duplicates all static variables on each modules and it causes that can't
    ///         check hierarchy properly.
    ///         sure, I can exports them,template classes, as external symbol for 3rd party modules to link
    ///         and make it act well. but this requires user to declare another macro or statements such as
    ///         burden to get them be annoy.
    ///         instead of that, I put those inside of static symbols at normal nested private class.
    ///         now, TClass of course will be duplicated on each modules and code bloated but it will act
    ///         like proxy pointing this nested class.
    ///
    ///         in conclusion, users can ignore this background reasons and use WRD_CLASS macro without
    ///         additional consideration.
    template <typename T>
    struct tnameGetter {
        static const wchar* getRawName() { return typeid(T).name(); }
        static std::string getName() { return nameDemangler::demangle(getRawName()); }
    };

    // famous void_t def:
    //  predefined at c++17 (if we use c++17, we can remove this)
    template <typename T>
    using void_t = void;

    // superTypeChecker:
    //  if user defined superType on their own, we let their TType classes inherit their superType class.
    //  otherwise, just use Type as base class.
    template <typename T, typename = void>
    struct tsuperTypeDef {
        using is = type;
    };
    template <typename T>
    struct tsuperTypeDef<T, void_t<int T::superType::*>> {
        using is = typename T::superType;
    };
 }
