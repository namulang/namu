#include "NEClassBase.hpp"
#include "../Kernal/Kernal.hpp"
#include "../NEClassBaseList/NEClassBaseList.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
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

	bool NE_DLL NEClassBase::isEqualTypeWith(const This& source) const
	{
		return	&source							&&
				&getName() == &source.getName()	;
	}

	bool NE_DLL NEClassBase::isEqualTypeWith(const NEObject& source) const
	{
		return isEqualTypeWith(source.getClass());
	}

	bool NE_DLL NEClassBase::isSuperClassOf(const This& parent) const
	{
		return Kernal::getInstance().getTypeManager().isHierarchy(*this, parent);
	}

	bool NE_DLL NEClassBase::isSuperClassOf(const NEObject& parent) const
	{
		return isSuperClassOf(parent.getClass());
	}

	bool NE_DLL NEClassBase::isSubClassOf(const This& parent) const
	{
		return Kernal::getInstance().getTypeManager().isHierarchy(parent, *this);
	}

	bool NE_DLL NEClassBase::isSubClassOf(const NEObject& parent) const
	{
		return isSubClassOf(parent.getClass());
	}

	type_result NEClassBase::_registerSubClass(const NEClassBase& subclass)
	{
		//	pre:
		//		Never use the method of instance to check whether given subclass is a kind of Unknown.
		//		If do so, definitely, you will get some damn happy feelings because of a infinite recursive call.
		if(&subclass.getName() == &NETClass<NEObject>::getNameStatically())
			return RESULT_SUCCESS;


		//	main:
		//		Acquire static instance:	you can use this now. Above recursive trap has been cleared :)
		static NETClass<NEObject> root_class;
		//		This statement makes a recursive call in order to register super type.
		const NEClassBase& super = subclass.getSuperClass();
		if(*this == super) 
			return _registerSubClassAsMyChild(subclass);

		NEClassBaseList& subs = _getSubClasses();
		for(int n=0; n < subs.getLength() ;n++)
			if(subs[n]._registerSubClass(subclass) == RESULT_SUCCESS)
				return RESULT_SUCCESS;


		//	post:
		return RESULT_COULDNOT_FIND_DATA;
	}

	type_result NEClassBase::_registerSubClassAsMyChild(const NEClassBase& subclass)
	{
		type_index pushed_index = _getSubClasses().push(subclass);
		if(pushed_index == NE_INDEX_ERROR)
			return RESULT_TYPE_WARNING;

		return RESULT_SUCCESS;
	}

	NEClassBaseList& NEClassBase::_getSubClasses()
	{
		return const_cast<NEClassBaseList&>(getSubClasses());
	}

	const This NE_DLL &NEClassBase::getSuperClass() const
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

	type_result NEClassBase::enroll()
	{
		if(isRegistered()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		Kernal& kernel = Kernal::getInstance();
		if( ! &kernel) return RESULT_TYPE_ERROR;
		NETypeManager& cm = kernel.getTypeManager();
		if( ! &cm) return RESULT_TYPE_ERROR;

		return cm.enroll(*this);
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
}