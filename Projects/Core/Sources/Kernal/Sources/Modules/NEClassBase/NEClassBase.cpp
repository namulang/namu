#include "NEClassBase.hpp"
#include "../NEHeader/NEHeader.hpp"
#include "../NETClass/NETClass.hpp"
#include "../NEClassBaseList/NEClassBaseList.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	NE_DEFINE_INTERFACE_ONLY(NEClassBase)

	typedef NEClassBase This;

	NE_DLL This::This()
		: Super()
	{

	}

	NE_DLL This::This(const This& source)
		: Super(source)
	{

	}

	NE_DLL This::~This()
	{

	}

	type_bool This::operator==(const This& rhs) const
	{
		return isEqualClassTo(rhs);
	}

	type_bool This::operator!=(const This& rhs) const
	{
		return ! operator==(rhs);
	}

	This& This::operator=(const This& rhs)
	{
		//	nothing to assign. can't be assigned.

		return *this;
	}	


	type_bool NE_DLL This::isEqualClassTo(const This& source) const
	{
		return	&source							&&
			&getName() == &source.getName()	;
	}

	type_bool NE_DLL This::isEqualClassTo(const NEObject& source) const
	{
		return isEqualClassTo(source.getClass());
	}

	type_bool NE_DLL This::isSuperClassOf(const This& parent) const
	{
		return Kernal::getInstance().getClassManager().isHierarchy(*this, parent);
	}

	type_bool NE_DLL This::isSuperClassOf(const NEObject& parent) const
	{
		return isSuperClassOf(parent.getClass());
	}

	type_bool NE_DLL This::isSubClassOf(const This& parent) const
	{
		return Kernal::getInstance().getClassManager().isHierarchy(parent, *this);
	}

	type_bool NE_DLL This::isSubClassOf(const NEObject& parent) const
	{
		return isSubClassOf(parent.getClass());
	}

	type_result This::_enrollSuperClasses(const This& new_super)
	{
		//	pre:
		//		targetting:
		NEClassBaseList& supers = _getSuperClasses();
		supers = new_super.getSuperClasses();


		//	post:
		supers.pushFront(new_super);

		return RESULT_SUCCESS;
	}

	type_result This::_enrollChildClass(const This& new_child)
	{
		return _getChildrenClasses().push(new_child);
	}

	NEClassBaseList& This::_getChildrenClasses()
	{
		return const_cast<NEClassBaseList&>(getSubClasses());
	}

	NEClassBaseList& This::_getSuperClasses()
	{
		return const_cast<NEClassBaseList&>(getSuperClases());
	}

	NEObject& This::instantiate() const
	{
		NEObject* nullptr = 0x00;
		KERNAL_WARNING("You can't instantiate interface class.");

		return *nullptr;
	}

	const This NE_DLL &This::getSuper() const
	{	
		//	if there is no ancestors, this will return null-referenced "This&" type.

		return getSuperClasses()[0];
	}

	type_result This::isValid() const
	{
		return RESULT_SUCCESS;
	}

	void This::release()
	{

	}

	NEBinaryFileSaver& This::serialize(NEBinaryFileSaver& saver) const
	{
		//	TODO:
		return saver;
	}

	NEBinaryFileLoader& This::serialize(NEBinaryFileLoader& loader)
	{
		//	TODO:
		return loader;
	}

	type_result This::_onInitializeHeader(NEHeader& to_initialize)
	{
		return RESULT_SUCCESS;
	}
	type_result This::_onInitializeMethods(NEMethodList& to_initialize)
	{
		return RESULT_SUCCESS;
	}

	NEHeader& This::_getHeader()
	{
		return const_cast<NEHeader&>(getHeader());
	}

	type_id& This::_getId()
	{
		return const_cast<type_id&>(getId());
	}

	type_result This::_setPackage(const NEPackage& new_package)
	{
		const NEPackagePtr& pointer = _getPackage();

		pointer = &new_package;

		return 0;
	}

	const NEPackage& This::getPackage() const
	{
		return *_getPackage();
	}
}