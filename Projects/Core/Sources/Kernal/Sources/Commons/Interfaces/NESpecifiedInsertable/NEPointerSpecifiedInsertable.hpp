#pragma once

namespace NE
{
	template <typename OutsideType>
	class NE_DLL NESpecifiedInsertable<OutsideType*>
	{
	public:
		virtual type_index insert(type_index index, const OutsideType* const source) = 0;
		virtual type_index remove(type_index) = 0;		
	};
}