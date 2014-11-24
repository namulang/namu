#include "NEArgumentTemplate.hpp"

namespace NE
{
	NEArgumentTemplate<NEKey>::NEArgumentTemplate(const ThisClass& rhs)
		: SuperClass(rhs)
	{

	}

	NEArgumentTemplate<NEKey>::NEArgumentTemplate()
		: SuperClass(NEType::NEKEY)
	{

	}

	NEObject& NEArgumentTemplate<NEKey>::clone() const
	{
		return *(new ThisClass(*this));
	}

	type_result NEArgumentTemplate<NEKey>::update()
	{
		return RESULT_SUCCESS;
	}
}