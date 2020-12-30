#pragma once

#include "../common.hpp"
#include "./type/Adam.hpp"

namespace wrd { namespace meta {

    class MetaIf {
    protected:
        typedef short yes;
        typedef char no;
    };

    template <typename T>
    struct TIfTemplate : public MetaIf {
        template <template<typename> class Template, typename X>
        static yes _foo(Template<X>*);
        static no _foo(...);

        static inline constexpr wbool is = sizeof(_foo((T*)0)) == sizeof(yes);
    };

    template <typename T, typename Super> // is T is sub of Super
    struct TIfSub {
        static inline constexpr wbool is = std::is_base_of<Super, T>::value;
    };

    template <typename T>
    struct TIfAbstract {
        static inline constexpr wbool is = std::is_abstract<T>::value;
    };

    template <typename T>
    struct TAEmptyCan {
        typedef void is;
    };
    template <typename T, typename = void>
    struct TIfHasSuperTypedef : public MetaIf {
        static inline constexpr wbool is = false;
    };
    template <typename T>
    struct TIfHasSuperTypedef<T, typename TAEmptyCan<typename T::Super>::is> : public MetaIf {
        static inline constexpr wbool is = true;
    };

    template <typename T, wbool typedefSuper = TIfHasSuperTypedef<T>::is>
    struct TAdaptiveSuper : MetaIf {
        typedef Adam Super;
    };
    template <typename T>
    struct TAdaptiveSuper<T, true> {
        typedef typename T::Super Super;
    };

    template <typename T, wbool is_adt = TIfAbstract<T>::is>
    struct TInstanceMaker {
		static void* make() { return WRD_NULL; }
    };
    template <typename T>
    struct TInstanceMaker<T, false> {
		static void* make() { return new T(); }
    };

    struct NameDemangler {
		static std::string demangle(const wchar* org) {
            wchar* demangled = WRD_NULL;
            int status = 0;

            demangled = ::abi::__cxa_demangle(org, 0, 0, &status);
            std::string ret(demangled);

            free(demangled);
            return ret;
        }
	};

	///	@remark	TClass is a class template using monostate pattern.
	///			so it duplicates all static variables on each modules and it causes that can't
	///			check hierarchy properly.
	///			sure, I can exports them,template classes, as external symbol for 3rd party modules to link
	///			and make it act well. but this requires user to declare another macro or statements such as
	///			burden to get them be annoy.
	///			instead of that, I put those inside of static symbols at normal nested private class.
	///			now, TClass of course will be duplicated on each modules and code bloated but it will act
	///			like proxy pointing	this nested class.
	///
	///			in conclusion, users can ignore this background reasons and use WRD_CLASS macro without
	///			additional consideration.
    template <typename T>
	struct TNameGetter {
        static const wchar* getRawName() { return typeid(T).name(); }
        static std::string getName() { return NameDemangler::demangle(getRawName()); }
    };

} }
