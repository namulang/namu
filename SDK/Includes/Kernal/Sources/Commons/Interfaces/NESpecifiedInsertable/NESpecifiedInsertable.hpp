#pragma once

namespace NE
{
	template <typename OutsideType>
	class NESpecifiedInsertable
	{
	public:
		virtual type_index insert(type_index index, const OutsideType& source) = 0;
		virtual type_index remove(type_index) = 0;		
	};
}

#include "NEPointerSpecifiedInsertable.hpp"