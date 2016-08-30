#include "NETClassMetaClass.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	//	We can't use NE_DEFINE_CLASS_ONLY macros at here:
	//		because we're defining NETClassMetaClass as NETClass<NETClass<...>> 
	//		in order to avoid templating infinitely.
	//		So, in this part, we have to define methods declared at header files
	//		manually.
	const NEClassBase& NETClassMetaClass::getClass() const { return getClassStatically(); }
	const NEClassBase& NETClassMetaClass::getClassStatically() 
	{
		static This _inner;

		return _inner;
	}
	NEObject& NETClassMetaClass:clone() const
	{
		return *(new This(this));
	}

	const NEPackagePtr& NETClassMetaClass::_getPackage() const
	{
		static NEPackage* _inner = NE_NULL;

		return _inner;
	}

	const type_bool& NETClassMetaClass::isRegisteredStatically()
	{
		static type_bool _inner;

		return _inner;
	}

	type_bool NETClassMetaClass::isMetaClassDefinedStatically() { return false; }
	type_bool NETClassMetaClass::isInstantiableStatically() { return false; }
	type_bool NETClassMetaClass::isTemplateStatically() { return true; }
	type_bool NETClassMetaClass::isBuiltInClassStatically() { return true; }

	const NEClassBase& NETClassMetaClass::getTraitClassStatically()
	{
		static NETClass<NEUnknown> _inner;

		return _inner;
	}

	const NEClassBaseList& NETClassMetaClass::getSuperClassesStatically()
	{
		static NEClassBaseList _inner;

		return _inner;
	}

	const NEClassBaseList& NETClassMetaClass::getChildrenClassesStatically()
	{
		static NEClassBaseList _inner;

		return _inner;
	}

	const NEHeader& NETClassMetaClass::getHeaderStatically()
	{
		static NEHeader _inner;

		return _inner;
	}

	const NETString& NETClassMetaClass::getNameStatically()
	{
		static NETString _inner("NETClass<T>");

		return _inner;
	}

	const type_id& NETClassMetaClass::getIdStatically()
	{
		static type_id inner;

		return inner;
	}

	type_bool NETClassMetaClass::isInstantiable() const	{ return isInstantiableStatically(); }
	type_bool NETClassMetaClass::isTemplate() const { return isTemplateStatically(); }
	type_bool NETClassMetaClass::isMetaClassDefined() const { return isMetaClassDefinedStatically(); }
	const type_bool& NETClassMetaClass::isRegistered() const { return isRegisteredStatically(); }
	const NEClassBase& NETClassMetaClass::getTraitClass() const { return *this; }
	const NEClassBaseList& NETClassMetaClass::getSuperClasses() const { return getSuperClassesStatically(); }
	const NEClassBaseList& NETClassMetaClass::getChildrenClasses() const { return getChildrenClassesStatically(); }
	const NETString& NETClassMetaClass::getName() const	{ return getNameStatically(); }
	NEObject& NETClassMetaClass::instantiate() const
	{
		NEObject* nullptr = 0x00;
		KERNAL_ERROR("can't instantiate %s class.", getName().toCharPointer());

		return *nullptr;
	}
	NEObject& NETClassMetaClass::getHeader() const { return getHeaderStatically(); }
	const NEPackagePtr& NETClassMetaClass::_getPackage() const
	{
		static NEPackage* inner = NE_NULL;

		return inner;
	}

}