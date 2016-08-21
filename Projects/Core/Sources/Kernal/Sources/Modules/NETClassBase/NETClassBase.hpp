#include "NETClassBase.inl"
#include "NETClass.hpp"
#include "../NEPackage/NEPackage.hpp"
#include "../NETDerivedClassChecker/NETDerivedClassChecker.hpp"
#include "../NETTemplateChecker/NETTemplateChecker.hpp"
//	We must include ADTChecker after loaded TClass declarations and its 
//	implementations(= TClass.hpp).
//	Why do we have to keep this sequence:
//		in order to use ADTChecker including TClass must be predeterminded first.
//		because ADTChecker can checks whether T is kind of Interface Class by 
//		applying SFINAE with TInterfaceClass(is part of TClass.hpp)
#include "../NETADTChecker/NETADTChecker.hpp"
//	Following one is just same as above.
#include "../NETUnknownMetaClass/NETUnknownMetaClass.hpp"

namespace NE
{
	template <typename T>
	const NEClassBase& NETClassBase<T>::getClass() const
	{
		return getClassStatically();
	}

	template <typename T>
	const NEClassBase& NETClassBase<T>::getClassStatically()
	{
		static NETClass<This> inner;

		return inner;
	}

	template <typename T>
	const NETString& NETClassBase<T>::getName() const
	{
		return getNameStatically();
	}

	template <typename T>
	const NEClassBaseList& NETClassBase<T>::getSuperClasses() const
	{
		return getSuperClassesStatically();
	}

	template <typename T>
	const NEClassBaseList& NETClassBase<T>::getChildrenClasses() const
	{
		return getChildrenClassesStatically();
	}

	template <typename T>
	const NEClassBase& NETClassBase<T>::getClass() const
	{
		return getClassStatically();
	}

	template <typename T>
	type_bool NETClassBase<T>::isMetaClassDefined() const
	{
		return isMetaClassDefinedStatically();
	}

	template <typename T>
	type_bool NETClassBase<T>::isInstantiable() const
	{
		return isInstantiableStatically();
	}

	template <typename T>
	type_bool NETClassBase<T>::isTemplate() const
	{
		return isTemplateStatically();
	}

	template <typename T>
	type_bool NETClassBase<T>::isBuiltInClass() const
	{
		return isBuiltInClassStatically();
	}

	template <typename T>
	const NEClassBase& NETClassBase<T>::getTraitClass() const
	{
		return getTraitClassStatically();
	}


	template <typename T>
	const NETString& NETClassBase<T>::getNameStatically()
	{
		static NETString _inner;

		if (_inner.getLength() <= 0)
			_inner = typeid(T).name();

		return _inner;
	}

	template <typename T>
	const NEClassBase& NETClassBase<T>::getClassStatically()
	{
		//	What is this:
		//		When NETClass is templated with some parameter type T,
		//		it's a problem to provide metaclass of NETClass. (of course, 
		//		because NETClass is a kind of metaclass, giving metaclass of
		//		metaclass is the problem mentioned above)
		//		The reason which this going to be a problem is templating reculsively.
		//		Just imagine NETClass<T> that is returning NETClass<NETClass<T> for
		//		its metaclass.
		//		so, this get crack the codes. to prevent this, we replace metaclass
		//		to NETMetaClass. Dummy.
		//		All NETClass<T> will return NETClass<NETMetaClass>() for getClass()
		//		method.
		static NETClass<NETMetaClass> inner;

		return inner;
	}

	template <typename T>
	const NEIdentifier& NETClassBase<T>::getHeader() const
	{
		return getHeaderStatically();
	}

	template <typename T>
	const NEIdentifier& NETClassBase<T>::getHeaderStatically()
	{
		static NEHeader _inner;

		return _inner;
	}

	template <typename T>
	const type_bool& NETClassBase<T>::isRegisteredStatically()
	{
		static type_bool _inner;

		return _inner;
	}

	template <typename T>
	const NEClassBaseList& NETClassBase<T>::getSuperClassesStatically()
	{
		static NEClassBaseList _inner;

		return _inner;
	}
	template <typename T>
	const NEClassBaseList& NETClassBase<T>::getChildrenClassesStatically()
	{
		static NEClassBaseList _inner;

		return _inner;
	}

	template <typename T>
	type_id NEClassBaseList& NETClassBase<T>::getId() const
	{
		return getIdStatically();
	}

	template <typename T>
	const type_id& NETClassBase<T>::getIdStatically()
	{
		static type_id _inner;

		return _inner;
	}

	template <typename T>
	const NEClassBase& NETClassBase<T>::getTraitClassStatically()
	{
		static NETClass<Trait> _inner;

		return _inner;
	}

	template <typename T>
	type_bool NETClassBase<T>::isBuiltInClassStatically()
	{
		return NETDerivedClassChecker<T, NEObject>::IS_DERIVED_OF;
	}

	template <typename T>
	type_bool NETClassBase<T>::isTemplateStatically()
	{
		return NETTemplateChecker<T>::IS_TEMPLATE;
	}

	template <typename T>
	type_bool NETClassBase<T>::isInstantiableStatically()
	{
		return NETADTChecker<T>::IS_ADT;
	}

	template <typename T>
	type_bool NETClassBase<T>::isMetaClassDefinedStatically()
	{
		return NETMetaClassChecker<T>::IS_METACLASS_DEFINED;
	}

	template <typename T>
	const NEPackage& NETClassBase<T>::getPackage() const
	{
		static NEPackage instance;

		return instance;
	}

	template <typename T>
	NEObject& NETClassBase<T>::clone() const
	{
		return *(new This(*this));
	}
}