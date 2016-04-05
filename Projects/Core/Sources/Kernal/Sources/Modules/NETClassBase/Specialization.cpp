#include "../NETClass/NETClass.hpp"
#include "NETClassBase.hpp"
#include "../NEClassBaseList/NEClassBaseList.hpp"
#include "../NEWString/NEWString.hpp"
#include "../NEString/NEString.hpp"

namespace NE
{
	type_bool NETClassBase<NEUnknown>::isMetaClassDefined() const
	{
		return IS_METACLASS_DEFINED;
	}

	type_bool NETClassBase<NEUnknown>::isInstantiable() const
	{
		return IS_ADT;    //    Can't know because World check whether it's by MetaClass.
	}

	type_bool NETClassBase<NEUnknown>::isTemplate() const
	{
		return IS_TEMPLATE;
	}

	type_bool NETClassBase<NEUnknown>::isBuiltInClass() const
	{
		return IS_BUILT_IN_CLASS;
	}

	const NEClassBase& NETClassBase<NEUnknown>::getTraitClass() const
	{
		return getTraitClassStatically();
	}

	const NEClassBase& NETClassBase<NEUnknown>::getTraitClassStatically()
	{
		static NETClass<NEUnknown> _inner;

		return _inner;
	}

	//////////////////////////////////////////////////////////////////////////

	type_bool NETClassBase<NEAdam>::isMetaClassDefined() const
	{
		return IS_METACLASS_DEFINED;
	}

	type_bool NETClassBase<NEAdam>::isInstantiable() const
	{
		return IS_ADT;    //    Can't know because World check whether it's by MetaClass.
	}

	type_bool NETClassBase<NEAdam>::isTemplate() const
	{
		return IS_TEMPLATE;
	}

	type_bool NETClassBase<NEAdam>::isBuiltInClass() const
	{
		return IS_BUILT_IN_CLASS;
	}

	const NEClassBase& NETClassBase<NEAdam>::getTraitClass() const
	{
		return getTraitClassStatically();
	}

	const NEClassBase& NETClassBase<NEAdam>::getTraitClassStatically()
	{
		static NETClass<NEUnknown> _inner;

		return _inner;
	}

	//////////////////////////////////////////////////////////////////////////

	type_bool NETClassBase<NEObject>::isMetaClassDefined() const
	{
		return IS_METACLASS_DEFINED;
	}

	type_bool NETClassBase<NEObject>::isInstantiable() const
	{
		return IS_ADT;    //    Can't know because World check whether it's by MetaClass.
	}

	type_bool NETClassBase<NEObject>::isTemplate() const
	{
		return IS_TEMPLATE;
	}

	type_bool NETClassBase<NEObject>::isBuiltInClass() const
	{
		return IS_BUILT_IN_CLASS;
	}

	const NEClassBase& NETClassBase<NEObject>::getTraitClass() const
	{
		return getTraitClassStatically();
	}

	const NEClassBase& NETClassBase<NEObject>::getTraitClassStatically()
	{
		static NETClass<NEObject> _inner;

		return _inner;
	}

	//////////////////////////////////////////////////////////////////////////

	type_bool NETClassBase<NEIdableObject>::isMetaClassDefined() const
	{
		return IS_METACLASS_DEFINED;
	}

	type_bool NETClassBase<NEIdableObject>::isInstantiable() const
	{
		return IS_ADT;    //    Can't know because World check whether it's by MetaClass.
	}

	type_bool NETClassBase<NEIdableObject>::isTemplate() const
	{
		return IS_TEMPLATE;
	}

	type_bool NETClassBase<NEIdableObject>::isBuiltInClass() const
	{
		return IS_BUILT_IN_CLASS;
	}

	const NEClassBase& NETClassBase<NEIdableObject>::getTraitClass() const
	{
		return getTraitClassStatically();
	}

	const NEClassBase& NETClassBase<NEIdableObject>::getTraitClassStatically()
	{
		static NETClass<NEIdableObject> _inner;

		return _inner;
	}

	//////////////////////////////////////////////////////////////////////////

	type_bool NETClassBase<NEClassBase>::isMetaClassDefined() const
	{
		return IS_METACLASS_DEFINED;
	}

	type_bool NETClassBase<NEClassBase>::isInstantiable() const
	{
		return IS_ADT;    //    Can't know because World check whether it's by MetaClass.
	}

	type_bool NETClassBase<NEClassBase>::isTemplate() const
	{
		return IS_TEMPLATE;
	}

	type_bool NETClassBase<NEClassBase>::isBuiltInClass() const
	{
		return IS_BUILT_IN_CLASS;
	}

	const NEClassBase& NETClassBase<NEClassBase>::getTraitClass() const
	{
		return getTraitClassStatically();
	}

	const NEClassBase& NETClassBase<NEClassBase>::getTraitClassStatically()
	{
		static NETClass<NEClassBase> _inner;

		return _inner;
	}

	//////////////////////////////////////////////////////////////////////////

	type_bool NETClassBase<NEModule>::isMetaClassDefined() const
	{
		return IS_METACLASS_DEFINED;
	}

	type_bool NETClassBase<NEModule>::isInstantiable() const
	{
		return IS_ADT;    //    Can't know because World check whether it's by MetaClass.
	}

	type_bool NETClassBase<NEModule>::isTemplate() const
	{
		return IS_TEMPLATE;
	}

	type_bool NETClassBase<NEModule>::isBuiltInClass() const
	{
		return IS_BUILT_IN_CLASS;
	}

	const NEClassBase& NETClassBase<NEModule>::getTraitClass() const
	{
		return getTraitClassStatically();
	}

	const NEClassBase& NETClassBase<NEModule>::getTraitClassStatically()
	{
		static NETClass<NEModule> _inner;

		return _inner;
	}
}