#pragma once

#include "../NENumericType/NENumericType.hpp"

namespace NE
{
	class NE_DLL NEInteger : public NENumericType
	{
		NE_DECLARE_CLASS(NEInteger, NENumericType)

	public:
		virtual type_result isValid() const;
	};
}