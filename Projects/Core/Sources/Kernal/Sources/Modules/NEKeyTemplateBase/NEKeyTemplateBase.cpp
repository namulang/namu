#include "NEKeyTemplateBase.hpp"
#include "../NEKeySelector/NEKeySelector.hpp"

namespace NE
{
	type_result NEKeyTemplateBase::assign(const NEKey& source)
	{
		if( ! &source) return RESULT_TYPE_ERROR;
		if( this == &source) return RESULT_TYPE_ERROR;

		SuperClass::assign(source);

		type_result result = RESULT_SUCCESS;
		if(source.getType() == NEType::NEKEY_SELECTOR)
		{
			NEKeySelector copied = static_cast<const NEKeySelector&>(source);

			while(NEKey* itr = &copied.getKey())
				result |= assign(*itr);
		}

		return result;
	}

	NEKeyTemplateBase::NEKeyTemplateBase(const NETString& new_keyname)
		: SuperClass(new_keyname)
	{

	}

	NEKeyTemplateBase::NEKeyTemplateBase(const ThisClass& source)
		: SuperClass(source)
	{

	}

	NEKeyTemplateBase::~NEKeyTemplateBase()
	{

	}
}