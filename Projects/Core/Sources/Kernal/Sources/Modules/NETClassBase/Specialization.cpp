#include "../NEClassBase/NEClassBase.hpp"
#include "NETClassBase.hpp"
#include "../NETClass/NETClass.hpp"
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

	const type_bool& NETClassBase<NEUnknown>::isRegistered() const
	{
		return isRegisteredStatically();
	}

	const NEClassBase& NETClassBase<NEUnknown>::getTraitClass() const
	{
		return getTraitClassStatically();
	}

	const NEClassBaseList& NETClassBase<NEUnknown>::getSuperClasses() const
	{
		return getSuperClassesStatically();
	}

	const NEClassBaseList& NETClassBase<NEUnknown>::getSubClasses() const
	{
		return getSubClassesStatically();
	}

	const NETString& NETClassBase<NEUnknown>::getName() const
	{
		return getNameStatically();
	}

	const NEClassBase& NETClassBase<NEUnknown>::getClass() const
	{
		return getClassStatically();
	}

	type_result NETClassBase<NEUnknown>::_setRegistered(type_bool new_is_registered)
	{
		type_bool& casted = const_cast<type_bool&>(isRegisteredStatically());

		casted = new_is_registered;

		return RESULT_SUCCESS;
	}

	const NEClassBase& NETClassBase<NEUnknown>::getTraitClassStatically()
	{
		static NETClass<NEUnknown> _inner;

		return _inner;
	}

	const NETString& NETClassBase<NEUnknown>::getNameStatically()
	{
		static NETString _inner(typeid(Trait).name());

		return _inner;
	}


	const type_bool& NETClassBase<NEUnknown>::isRegisteredStatically()
	{
		static type_bool _inner = false;

		return _inner;
	}

	const NEClassBaseList& NETClassBase<NEUnknown>::getSuperClassesStatically()
	{
		static NEClassBaseList& _inner;

		return _inner;
	}

	const NEClassBaseList& NETClassBase<NEUnknown>::getSubClassesStatically()
	{
		static NEClassBaseList& _inner;

		return _inner;
	}

	const NEClassBase& NETClassBase<NEUnknown>::getClassStatically()
	{
		static NETClass<NEUnknown> _inner;

		return _inner;
	}



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

	const type_bool& NETClassBase<NEAdam>::isRegistered() const
	{
		return isRegisteredStatically();
	}

	const NEClassBase& NETClassBase<NEAdam>::getTraitClass() const
	{
		return getTraitClassStatically();
	}

	const NEClassBaseList& NETClassBase<NEAdam>::getSuperClasses() const
	{
		return getSuperClassesStatically();
	}

	const NEClassBaseList& NETClassBase<NEAdam>::getSubClasses() const
	{
		return getSubClassesStatically();
	}

	const NETString& NETClassBase<NEAdam>::getName()
	{
		return getNameStatically();
	}

	const NEClassBase& NETClassBase<NEAdam>::getClass()
	{
		return getClassStatically();
	}

	type_result NETClassBase<NEAdam>::_setRegistered(type_bool new_is_registered)
	{
		type_bool& casted = const_cast<type_bool&>(isRegisteredStatically());

		casted = new_is_registered;

		return RESULT_SUCCESS;
	}

	const NEClassBase& NETClassBase<NEAdam>::getTraitClassStatically()
	{
		static NETClass<NEUnknown> _inner;

		return _inner;
	}

	const NETString& NETClassBase<NEAdam>::getNameStatically()
	{
		static NETString _inner(typeid(Trait).name());

		return _inner;
	}

	const type_bool& NETClassBase<NEAdam>::isRegisteredStatically()
	{
		static type_bool _inner = false;

		return _inner;
	}

	const NEClassBaseList& NETClassBase<NEAdam>::getSuperClassesStatically()
	{
		static NEClassBaseList& _inner;

		return _inner;
	}

	const NEClassBaseList& NETClassBase<NEAdam>::getSubClassesStatically()
	{
		static NEClassBaseList& _inner;

		return _inner;
	}

	const NEClassBase& NETClassBase<NEAdam>::getClassStatically()
	{
		static NETClass<NEAdam> _inner;

		return _inner;
	}
}