#pragma once

#include "../memory/TStrong.inl"

namespace wrd { namespace meta {

    class MetaIf
    {
    protected:
        typedef short yes;
        typedef char no;
    };

    // inspired by boost::is_abstract()
    template <typename T>
    struct TIfAbstract : public MetaIf
    {
        template <typename U> static no _foo(U (*)());
        template <typename U> static yes _foo(...);

        static const wbool is = sizeof(TIfAbstract<T>::template _foo<T>(0)) == sizeof(yes);
    };

    template <typename T>
    struct TIfTemplate : public MetaIf
    {
        template <template<typename> class Template, typename X>
        static yes _foo(Template<X>*);
        static no _foo(...);

        static const wbool is = sizeof(_foo((T*)0)) == sizeof(yes);
    };

    template <typename T, typename Super> // is T is sub of Super
    struct TIfSub : public MetaIf
    {
        static yes _foo(Super*);
        static no _foo(...);

        enum {
            is = sizeof(_foo((T*) 0)) == sizeof(yes)
        };
    };

    template <typename T>
    struct TAEmptyCan {
        typedef void is;
    }
    template <typename T>
    struct TIfHasSuperTypedef<T, typename TAEmptyCan<T::Super>::is> : public MetaIf {
        static const wbool is = false;
    }
    template <typename T, typename = void>
    struct TIfHasSuperTypedef : public MetaIf {
        static const wbool is = true;
    };

    template <typename T, wbool typedefSuper = TIfHasSuperTypedef<T>::is>
    struct TAdaptiveSuper : MetaIf {
        typedef Adam Super;
    };
    template <typename T>
    struct TAdaptiveSuper<T, true> {
        typedef T::Super Super;
    };

    template <typename T>
    struct TIfStaticMethod : public MetaIf
    {
        template <typename R, typename... Args>
        static yes _foo( R(*)(Args...) );
        static no _foo(...);

        static const bool is = sizeof(_foo( (T) 0 )) == sizeof(yes);
    };

    template <typename T, wbool is_adt = TIfAbstract<T>::is, wbool is_an_instance = TIfSub<T, Instance>::is>
    struct TInstanceMaker {
		static void* make() { return WRD_NULL; }
    };
    template <typename T>
    struct TInstanceMaker<T, false, true> {
		static void* make() { return new T(); }
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
    }

    struct NameDemangler {
		static std::string demangle(const wchar* org) {
            wchar* demangled = WRD_NULL;
            int status = 0;

            demangled = abi::__cxa_demangle(org, 0, 0, &status);
            std::string ret(demangled);

            free(demangled);
            return ret;
        }
	};
} }
