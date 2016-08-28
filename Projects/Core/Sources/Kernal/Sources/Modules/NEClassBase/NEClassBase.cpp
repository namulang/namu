#include "NEClassBase.hpp"
#include "../NEHeader/NEHeader.hpp"
#include "../NETClass/NETClass.hpp"
#include "../NEClassBaseList/NEClassBaseList.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	NE_DEFINE_INTERFACE_ONLY(NEClassBase)

	typedef NEClassBase This;

	NE_DLL NEClassBase::NEClassBase()
		: Super()
	{

	}

	NE_DLL NEClassBase::NEClassBase(const NEClassBase& source)
		: Super(source)
	{

	}

	NE_DLL NEClassBase::~NEClassBase()
	{

	}

	type_bool NE_DLL NEClassBase::isEqualClassTo(const This& source) const
	{
		return	&source							&&
			&getName() == &source.getName()	;
	}

	type_bool NE_DLL NEClassBase::isEqualClassTo(const NEObject& source) const
	{
		return isEqualClassTo(source.getClass());
	}

	type_bool NE_DLL NEClassBase::isSuperClassOf(const This& parent) const
	{
		return Kernal::getInstance().getClassManager().isHierarchy(*this, parent);
	}

	type_bool NE_DLL NEClassBase::isSuperClassOf(const NEObject& parent) const
	{
		return isSuperClassOf(parent.getClass());
	}

	type_bool NE_DLL NEClassBase::isSubClassOf(const This& parent) const
	{
		return Kernal::getInstance().getClassManager().isHierarchy(parent, *this);
	}

	type_bool NE_DLL NEClassBase::isSubClassOf(const NEObject& parent) const
	{
		return isSubClassOf(parent.getClass());
	}

	type_result NEClassBase::_enrollSuperClasses(const NEClassBase& new_super)
	{
		//	pre:
		//		targetting:
		NEClassBaseList& supers = _getSuperClasses();
		supers = new_super.getSuperClasses();


		//	post:
		supers.pushFront(new_super);

		return RESULT_SUCCESS;
	}

	type_result NEClassBase::_enrollChildClass(const NEClassBase& new_child)
	{
		return _getChildrenClasses().push(new_child);
	}

	NEClassBaseList& NEClassBase::_getChildrenClasses()
	{
		return const_cast<NEClassBaseList&>(getSubClasses());
	}

	NEClassBaseList& NEClassBase::_getSuperClasses()
	{
		return const_cast<NEClassBaseList&>(getSuperClases());
	}

	const This NE_DLL &NEClassBase::getSuper() const
	{	
		//	if there is no ancestors, this will return null-referenced "This&" type.

		return getSuperClasses()[0];
	}

	type_result NEClassBase::isValid() const
	{
		return RESULT_SUCCESS;
	}

	void NEClassBase::release()
	{

	}

	NEBinaryFileSaver& NEClassBase::serialize(NEBinaryFileSaver& saver) const
	{
		//	TODO:
		return saver;
	}

	NEBinaryFileLoader& NEClassBase::serialize(NEBinaryFileLoader& loader)
	{
		//	TODO:
		return loader;
	}

	type_result NEClassBase::_alert(type_result log_type, const type_tchar* message) const
	{
		//	pre:
		//		targetting:
		Kernal& kernel = Kernal::getInstance();
		if( ! &kernel) return RESULT_TYPE_ERROR;
		NEDebugManager& debugger = kernel.getDebugManager();

		//	main:
		type_int	bit_mask = RESULT_TYPE_ERROR | RESULT_TYPE_WARNING | RESULT_TYPE_INFORMATION;

		switch(log_type & bit_mask)
		{
		case RESULT_TYPE_ERROR:			RESULT_TYPE_ERROR(message);			break;

		case RESULT_TYPE_WARNING:		RESULT_TYPE_WARNING(message);		break;
		case RESULT_TYPE_INFORMATION:	RESULT_TYPE_INFORMATION(message);	break;
		}

		return log_type;
	}

	type_result NEClassBase::_onInitializeHeader(NEHeader& to_initialize)
	{
		return RESULT_SUCCESS;
	}
	type_result NEClassBase::_onInitializeMethods(NEMethodList& to_initialize)
	{
		return RESULT_SUCCESS;
	}

	NEHeader& NEClassBase::_getHeader()
	{
		return const_cast<NEHeader&>(getHeader());
	}

	type_id& NEClassBase::_getId()
	{
		return const_cast<type_id&>(getId());
	}

	type_result NEClassBase::_setPackage(const NEPackage& new_package)
	{
		const NEPackagePtr& pointer = _getPackage();

		pointer = &new_package;

		return 0;
	}

	const NEPackage& NEClassBase::getPackage() const
	{
		return *_getPackage();
	}
}