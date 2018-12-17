#pragma once

namespace wrd
{
    class MetaIf
    {
    protected:
        typedef short yes;
        typedef char no;
    };

    // inspired by boost::is_abstract()
    template <typename T>
    class TIfADT : public MetaIf
    {
        template <typename U> static no _foo(U (*)());
        template <typename U> static yes _foo(...);

    public:
        static const wbool is = sizeof(TIfADT<T>::template _foo<T>(0)) == sizeof(yes);
    };

    template <typename T>
    class TIfTemplate : public MetaIf
    {
        template <template<typename> class Template, typename X>
        static yes _foo(Template<X>*);
        static no _foo(...);

    public:
        static const wbool is = sizeof(_foo((T*)0)) == sizeof(yes);
    };

    template <typename T, typename Super> // is T is sub of Super
    class TIfSub : public MetaIf
    {
        static yes _foo(Super*);
        static no _foo(...);

    public:
        enum {
            is = sizeof(_foo((T*) 0)) == sizeof(yes)
        };
    };

    template <typename T>
    class TIfStaticMethod : public MetaIf
    {
        template <typename R, typename... Args>
        static yes _foo( R(*)(Args...) );
        static no _foo(...);

    public:
        static const bool is = sizeof(_foo( (T) 0 )) == sizeof(yes);
    };

	template <typename T, typename S>
	class TConcreteClass;

    template <wbool is>
    class TConcreteMeta
    {
    public:
        template <typename T, typename S>
		using Is = TConcreteClass<T, S>;
    };

	template <typename T, typename S>
	class TInterfaceClass;

    template <>
    class TConcreteMeta<false>
    {
    public:
        template <typename T, typename S>
        using Is = TInterfaceClass<T, S>;
    };

    /// whether given type T is sub class of T.
    ///    if it's a Object, its metaclass should have "Variable", a composition of pointing object's variables.
    class ObjectClass;

	template <wbool is>
    class TBaseMeta {
	public:
        typedef ObjectClass Is;
    };

	class Class;
    template <>
    class TBaseMeta<false> {
	public:
        typedef Class Is;
    };

    ///    TMetaSuper constructs final MetaClass against given type T regarding its hierarchy.
    //    normally it defines as, ... (baseclass depicted to high.
    //        - Class
    //        - [ObjectClass] only if T is sub class of Object.
    //        - [TConcreteClass || TInterfaceClass] determined whether type T is ADT or not.
    //        - TClass<T>
	class Object;
    template <typename T, wbool is_adt = TIfADT<T>::is, wbool is_mgd = TIfSub<T, Object>::is>
    class TMetaSuper {
	public:
		typedef typename TConcreteMeta<is_adt>::template Is<T, typename TBaseMeta<is_mgd>::Is> Is;
	};

    template <typename T, wbool is_adt = TIfADT<T>::is>
    class TCloner {
    public:
        static TStrong<Instance> clone(const T& origin) {
            return new T(origin);
        }
		static TStrong<Instance> instance() {
			return new T();
		}
    };
    template <typename T>
    class TCloner<T, true>
    public:
        static TStrong<Instance> clone(const T& origin) {
            return TStrong<Instance>();
        }
		static TStrong<Instance> instance() {
			return TStrong<Instance>();
		}
    };
}
