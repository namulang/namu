#include "NETClassBase.inl"

namespace NE
{
	template <typename T>
	type_bool NETClassBase<T>::isMetaClassDefined() const
	{
		return NETMetaClassChecker<T>::IS_METACLASS_DEFINED;
	}

	template <typename T>
	type_bool NETClassBase<T>::isTemplate() const
	{
		return NETTemplateChecker<T>::IS_TEMPLATE;
	}

	template <typename T>
	type_bool NETClassBase<T>::isBuiltInClass() const
	{
		return NETDerivedClassChecker<T, NEObject>::IS_DERIVED_OF;
	}

	template <typename T>
	const type_bool& NETClassBase<T>::isRegistered() const
	{
		return isRegisteredStatically();
	}

	template <typename T>
	const NEClassBase& NETClassBase<T>::getTraitClass() const
	{
		return getTraitClassStatically();
	}

	template <typename T>
	const NEClassBase& NETClassBase<T>::getTraitClassStatically()
	{
		static NETClass<Trait> _inner;

		return _inner;
	}
}