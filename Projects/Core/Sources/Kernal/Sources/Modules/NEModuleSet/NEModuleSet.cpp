#include "NEModuleSet.hpp"

namespace NE
{
	NEModuleSet::NEModuleSet()
		: Super() 
	{
	}
	NEModuleSet::NEModuleSet(type_count size)
		: Super(size)
	{

	}
	NEModuleSet::NEModuleSet(const This& rhs)
		: Super(rhs)
	{

	}
	NEModuleSet::~NEModuleSet()
	{

	}
	type_index NEModuleSet::insert(type_index index, const NEModule* const source)
	{
		type_index result_index = Super::insert(index, source);
		if(result_index == NE_INDEX_ERROR)
			return result_index;

		_updateModule(result_index);

		return result_index;
	}
	type_result NEModuleSet::setElement(type_index index, const NEModule* const source)
	{
		type_result result = Super::setElement(index, source);
		if( ! NEResult::hasError(result))
			_updateModule(index);

		return result;
	}

	void NEModuleSet::_updateModule(type_index index)
	{
		//		º¯°æ:
		NEModule& pushed = getElement(index);
		NECodeSet& scripts = pushed._getScriptCodes();
		scripts.create(1);
		scripts.push(NECode(index, NECodeType::SCRIPT));

		pushed._onFetchModule();
	}
}
