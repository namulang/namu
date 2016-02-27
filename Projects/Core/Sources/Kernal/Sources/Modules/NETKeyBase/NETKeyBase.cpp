#include "NETKeyBase.hpp"
#include "../NEKeySelector/NEKeySelector.hpp"

namespace NE
{
	type_result NETKeyBase::assign(const NEKey& source)
	{
		if( ! &source) return RESULT_TYPE_ERROR;
		if( this == &source) return RESULT_TYPE_ERROR;

		SuperClass::assign(source);

		type_result result = RESULT_SUCCESS;
		if(source.getType() == NEType::NEKEY_SELECTOR)
		{
			NEKeySelector copied = static_cast<const NEKeySelector&>(source);

			NEKey& itr = copied.getKey();
			if( &itr)
				result |= assign(itr);
		}

		return result;
	}

	NETKeyBase::NETKeyBase(const NETString& new_keyname)
		: SuperClass(new_keyname)
	{

	}

	NETKeyBase::NETKeyBase(const ThisClass& source)
		: SuperClass(source)
	{

	}

	NETKeyBase::~NETKeyBase()
	{

	}
}