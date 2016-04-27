#include "../NETClass/NETClass.hpp"
#include "NETClassBase.hpp"
#include "../NEClassBaseList/NEClassBaseList.hpp"
#include "../NEWString/NEWString.hpp"
#include "../NEString/NEString.hpp"

namespace NE
{
	type_bool NETClassBase<NEUnknown, false>::isMetaClassDefined() const
	{
		return IS_METACLASS_DEFINED;
	}

	type_bool NETClassBase<NEUnknown, false>::isInstantiable() const
	{
		return IS_ADT;    //    Can't know because World check whether it's by MetaClass.
	}

	type_bool NETClassBase<NEUnknown, false>::isTemplate() const
	{
		return IS_TEMPLATE;
	}

	type_bool NETClassBase<NEUnknown, false>::isBuiltInClass() const
	{
		return IS_BUILT_IN_CLASS;
	}

	const NEClassBase& NETClassBase<NEUnknown, false>::getTraitClass() const
	{
		return getTraitClassStatically();
	}

	const NEClassBase& NETClassBase<NEUnknown, false>::getTraitClassStatically()
	{
		static NETClass<NEUnknown, false> _inner;

		return _inner;
	}

	const NEIdentifier& NETClassBase<NEUnknown, false>::getIdentifier() const
	{
		return getIdentifierStatically();
	}

	const NEIdentifier& NETClassBase<NEUnknown, false>::getIdentifierStatically()
	{
		static NEIdentifier _inner;

		return _inner;
	}

	NEIdentifier& NETClassBase<NEUnknown, false>::_getIdentifier()
	{
		NEIdentifier& unlocked = const_cast<NEIdentifier&>(getIdentifierStatically());

		return unlocked;
	}

	//////////////////////////////////////////////////////////////////////////

	type_bool NETClassBase<NEAdam, false>::isMetaClassDefined() const
	{
		return IS_METACLASS_DEFINED;
	}

	type_bool NETClassBase<NEAdam, false>::isInstantiable() const
	{
		return IS_ADT;    //    Can't know because World check whether it's by MetaClass.
	}

	type_bool NETClassBase<NEAdam, false>::isTemplate() const
	{
		return IS_TEMPLATE;
	}

	type_bool NETClassBase<NEAdam, false>::isBuiltInClass() const
	{
		return IS_BUILT_IN_CLASS;
	}

	const NEClassBase& NETClassBase<NEAdam, false>::getTraitClass() const
	{
		return getTraitClassStatically();
	}

	const NEClassBase& NETClassBase<NEAdam, false>::getTraitClassStatically()
	{
		static NETClass<NEUnknown, false> _inner;

		return _inner;
	}

	const NEIdentifier& NETClassBase<NEAdam, false>::getIdentifier() const
	{
		return getIdentifierStatically();
	}

	const NEIdentifier& NETClassBase<NEAdam, false>::getIdentifierStatically()
	{
		static NEIdentifier _inner;

		return _inner;
	}

	NEIdentifier& NETClassBase<NEAdam, false>::_getIdentifier()
	{
		NEIdentifier& unlocked = const_cast<NEIdentifier&>(getIdentifierStatically());

		return unlocked;
	}

	//////////////////////////////////////////////////////////////////////////

	type_bool NETClassBase<NEObject, false>::isMetaClassDefined() const
	{
		return IS_METACLASS_DEFINED;
	}

	type_bool NETClassBase<NEObject, false>::isInstantiable() const
	{
		return IS_ADT;    //    Can't know because World check whether it's by MetaClass.
	}

	type_bool NETClassBase<NEObject, false>::isTemplate() const
	{
		return IS_TEMPLATE;
	}

	type_bool NETClassBase<NEObject, false>::isBuiltInClass() const
	{
		return IS_BUILT_IN_CLASS;
	}

	const NEClassBase& NETClassBase<NEObject, false>::getTraitClass() const
	{
		return getTraitClassStatically();
	}

	const NEClassBase& NETClassBase<NEObject, false>::getTraitClassStatically()
	{
		static NETClass<NEObject, false> _inner;

		return _inner;
	}

	const NEIdentifier& NETClassBase<NEObject, false>::getIdentifier() const
	{
		return getIdentifierStatically();
	}

	const NEIdentifier& NETClassBase<NEObject, false>::getIdentifierStatically()
	{
		static NEIdentifier _inner;

		return _inner;
	}

	NEIdentifier& NETClassBase<NEObject, false>::_getIdentifier()
	{
		NEIdentifier& unlocked = const_cast<NEIdentifier&>(getIdentifierStatically());

		return unlocked;
	}

	//////////////////////////////////////////////////////////////////////////

	type_bool NETClassBase<NEIdableObject, false>::isMetaClassDefined() const
	{
		return IS_METACLASS_DEFINED;
	}

	type_bool NETClassBase<NEIdableObject, false>::isInstantiable() const
	{
		return IS_ADT;    //    Can't know because World check whether it's by MetaClass.
	}

	type_bool NETClassBase<NEIdableObject, false>::isTemplate() const
	{
		return IS_TEMPLATE;
	}

	type_bool NETClassBase<NEIdableObject, false>::isBuiltInClass() const
	{
		return IS_BUILT_IN_CLASS;
	}

	const NEClassBase& NETClassBase<NEIdableObject, false>::getTraitClass() const
	{
		return getTraitClassStatically();
	}

	const NEClassBase& NETClassBase<NEIdableObject, false>::getTraitClassStatically()
	{
		static NETClass<NEIdableObject, false> _inner;

		return _inner;
	}

	const NEIdentifier& NETClassBase<NEIdableObject, false>::getIdentifier() const
	{
		return getIdentifierStatically();
	}

	const NEIdentifier& NETClassBase<NEIdableObject, false>::getIdentifierStatically()
	{
		static NEIdentifier _inner;

		return _inner;
	}

	NEIdentifier& NETClassBase<NEIdableObject, false>::_getIdentifier()
	{
		NEIdentifier& unlocked = const_cast<NEIdentifier&>(getIdentifierStatically());

		return unlocked;
	}

	//////////////////////////////////////////////////////////////////////////

	type_bool NETClassBase<NEClassBase, false>::isMetaClassDefined() const
	{
		return IS_METACLASS_DEFINED;
	}

	type_bool NETClassBase<NEClassBase, false>::isInstantiable() const
	{
		return IS_ADT;    //    Can't know because World check whether it's by MetaClass.
	}

	type_bool NETClassBase<NEClassBase, false>::isTemplate() const
	{
		return IS_TEMPLATE;
	}

	type_bool NETClassBase<NEClassBase, false>::isBuiltInClass() const
	{
		return IS_BUILT_IN_CLASS;
	}

	const NEClassBase& NETClassBase<NEClassBase, false>::getTraitClass() const
	{
		return getTraitClassStatically();
	}

	const NEClassBase& NETClassBase<NEClassBase, false>::getTraitClassStatically()
	{
		static NETClass<NEClassBase, false> _inner;

		return _inner;
	}

	const NEIdentifier& NETClassBase<NEClassBase, false>::getIdentifier() const
	{
		return getIdentifierStatically();
	}

	const NEIdentifier& NETClassBase<NEClassBase, false>::getIdentifierStatically()
	{
		static NEIdentifier _inner;

		return _inner;
	}

	NEIdentifier& NETClassBase<NEClassBase, false>::_getIdentifier()
	{
		NEIdentifier& unlocked = const_cast<NEIdentifier&>(getIdentifierStatically());

		return unlocked;
	}

	//////////////////////////////////////////////////////////////////////////

	template <typename T>
	type_bool NETClassBase<T, true>::isMetaClassDefined() const
	{
		return IS_METACLASS_DEFINED;
	}

	template <typename T>
	type_bool NETClassBase<T, true>::isInstantiable() const
	{
		return IS_ADT;    //    Can't know because World check whether it's by MetaClass.
	}

	template <typename T>
	type_bool NETClassBase<T, true>::isTemplate() const
	{
		return IS_TEMPLATE;
	}

	template <typename T>
	type_bool NETClassBase<T, true>::isBuiltInClass() const
	{
		return IS_BUILT_IN_CLASS;
	}

	template <typename T>
	const NEClassBase& NETClassBase<T, true>::getTraitClass() const
	{
		return getTraitClassStatically();
	}

	template <typename T>
	const NEClassBase& NETClassBase<T, true>::getTraitClassStatically()
	{
		static NETClass<T, true> _inner;

		return _inner;
	}

	template <typename T>
	const NEHeader& NETClassBase<T, true>::getIdentifier() const
	{
		return getIdentifierStatically();
	}

	template <typename T>
	const NEHeader& NETClassBase<T, true>::getIdentifierStatically()
	{
		static NEHeader _inner;

		return _inner;
	}

	template <typename T>
	NEHeader& NETClassBase<T, true>::_getIdentifier()
	{
		NEHeader& unlocked = const_cast<NEHeader&>(getIdentifierStatically());

		return unlocked;
	}
}