#include "NEObject.hpp"
#include "../NETClass.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	NE_DEFINE_INTERFACE_ONLY(NEObject)

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEObject::NEObject()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEObject::~NEObject() 
	{

	}		



	//	---------------------------------------------------------------------------------

	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEObject::NEObject(const This& source)
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-09-29	이태훈	작성
	//	---------------------------------------------------------------------------------
	type_bool NE_DLL NEObject::isEqualClassTo(const This& source) const 
	{
		return false;/*getType() == source.getType();*/
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-09-29	이태훈	작성
	//	---------------------------------------------------------------------------------
	type_bool NE_DLL NEObject::isSuperClassOf(const This& child) const 
	{
		return false; /*NEType::isValidHierachy(getType(), child.getType());*/
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-09-29	이태훈	작성
	//	---------------------------------------------------------------------------------
	type_bool NE_DLL NEObject::isSuperClassOf(const NEClassBase& child) const 
	{
		return false;/*NEType::isValidHierachy(getType(), child);*/
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-09-29	이태훈	작성
	//	---------------------------------------------------------------------------------
	type_bool NE_DLL NEObject::isSubClassOf(const This& parent) const 
	{
		return false; /*return NEType::isValidHierachy(parent.getType(), getType());*/
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-09-29	이태훈	작성
	//	---------------------------------------------------------------------------------
	type_bool NE_DLL NEObject::isSubClassOf(const NEClassBase& parent) const 
	{
		return false; /*return NEType::isValidHierachy(parent, getType());*/
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileSaver NE_DLL &NEObject::serialize(NEBinaryFileSaver& saver) const
	{
		return saver;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NEObject::serialize(NEBinaryFileLoader& loader)
	{
		return loader;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEObject::isValid() const  
	{
		//	type_code:		 
		if( ! isSubClassOf(ThisClass))
		{			
			KERNAL_ERROR("E000000C1 : 잘못된 타입\n 오브젝트인데, 타입은 Object가 아닙니다.\n타입=%s", getClass().getName())
			return RESULT_TYPE_WARNING | RESULT_INVALID_DATA;
		}

		return RESULT_SUCCESS;
	}
}
