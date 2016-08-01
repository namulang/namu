#include "NETClassBase.inl"
#include "NETClass.hpp"
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
	const NEClassBaseList& NETClassBase<T>::getSubClasses() const
	{
		return getSubClassesStatically();
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
		static NETClass<T> inner;

		return inner;
	}

	template <typename T>
	NEIdentifier& NETClassBase<T>::_getIdentifier()
	{
		NEIdentifier& casted = const_cast<NEIdentifier&>(getIdentifierStatically());

		return casted;
	}

	template <typename T>
	const NEIdentifier& NETClassBase<T>::getIdentifier() const
	{
		return getIdentifierStatically();
	}

	template <typename T>
	const NEIdentifier& NETClassBase<T>::getIdentifierStatically()
	{
		static NEIdentifier _inner;

		return _inner;
	}

	template <typename T>
	type_result NETClassBase<T>::_setRegistered(type_bool new_is_registered)
	{
		type_bool& is_registered = const_cast<type_bool&>(isRegisteredStatically());

		is_registered = new_is_registered;

		return RESULT_SUCCESS;
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
	const NEClassBaseList& NETClassBase<T>::getSubClassesStatically()
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
	type_result NETClassBase<T>::_setId(type_id new_id)
	{
		type_id& casted = const_cast<type_id&>(getIdStatically());

		casted = new_id;

		return RESULT_SUCCESS;
	}

	template <typename T>
	const NEClassBase& NE::NETClassBase<T>::getTraitClassStatically()
	{
		static NETClass<Trait> _inner;

		return _inner;
	}

	template <typename T>
	type_bool NE::NETClassBase<T>::isBuiltInClassStatically()
	{
		return NETDerivedClassChecker<T, NEObject>::IS_DERIVED_OF;
	}

	template <typename T>
	type_bool NE::NETClassBase<T>::isTemplateStatically()
	{
		return NETTemplateChecker<T>::IS_TEMPLATE;
	}

	template <typename T>
	type_bool NE::NETClassBase<T>::isInstantiableStatically()
	{
		return NETADTChecker<T>::IS_ADT;
	}

	template <typename T>
	type_bool NE::NETClassBase<T>::isMetaClassDefinedStatically()
	{
		return NETMetaClassChecker<T>::IS_METACLASS_DEFINED;
	}
}