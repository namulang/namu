#include "NETKeyBase.hpp"
#include "../NEKeySelector/NEKeySelector.hpp"

namespace NE
{
	type_result NETKeyBase::assign(const NEKey& source)
	{
		if( ! &source) return RESULT_TYPE_ERROR;
		if( this == &source) return RESULT_TYPE_ERROR;

		Super::assign(source);

		type_result result = RESULT_SUCCESS;
		if(source.isSubClassOf(NETClass<NEKeySelector()))
		{
			NEKeySelector copied = static_cast<const NEKeySelector&>(source);

			NEKey& itr = copied.getKey();
			if( &itr)
				result |= assign(itr);
		}

		return result;
	}

	NETKeyBase::NETKeyBase(const NETString& new_keyname)
		: Super(new_keyname)
	{

	}

	NETKeyBase::NETKeyBase(const This& source)
		: Super(source)
	{

	}

	NETKeyBase::~NETKeyBase()
	{

	}
}