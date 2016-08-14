#include "NEModuleDepthUnit.hpp"
#include "../../../Modules/NEModuleCodeSet/NEModuleCodeSet.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEModuleDepthUnit::NEModuleDepthUnit()
		: NEObject()
	{
		release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEModuleDepthUnit::NEModuleDepthUnit(type_index new_key_index)
		: NEObject(), key_index_to_be_moduleset(new_key_index)
	{		
		module_index = -1;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEModuleDepthUnit::NEModuleDepthUnit(const NEModuleDepthUnit& source)
		: NEObject(source)
	{
		_assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEModuleDepthUnit::~NEModuleDepthUnit()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_bool NE_DLL NEModuleDepthUnit::operator==(const NEModuleDepthUnit& source) const
	{
		if(this == &source) return true;
		if(module_index != source.module_index) return false;
		if(key_index_to_be_moduleset != source.key_index_to_be_moduleset) return false;

		return true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_bool NE_DLL NEModuleDepthUnit::operator!=(const NEModuleDepthUnit& source) const
	{
		return !(operator==(source));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEModuleDepthUnit NE_DLL &NEModuleDepthUnit::operator=(const NEModuleDepthUnit& source)
	{
		return _assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEModuleDepthUnit::release()
	{
		module_index = -1;
		key_index_to_be_moduleset = -1;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEModuleDepthUnit::isValid() const
	{		
		if(key_index_to_be_moduleset == -1) return RESULT_TYPE_WARNING | RESULT_WRONG_POINTER_ADDRESSING;

		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileSaver NE_DLL &NEModuleDepthUnit::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << key_index_to_be_moduleset << module_index;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NEModuleDepthUnit::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> key_index_to_be_moduleset >> module_index;
	}


	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEModuleDepthUnit &NEModuleDepthUnit::_assign(const NEModuleDepthUnit& source)
	{
		if(this == &source) return *this;

		key_index_to_be_moduleset = source.key_index_to_be_moduleset;
		module_index = source.module_index;

		return *this;
	}
}
