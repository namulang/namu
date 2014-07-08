#pragma once

#include "../../Functions/NEResult/NEResult.hpp"
#include "../../Templates/NEArrayTemplate/NEArrayTemplate.hpp"

namespace NE
{
	class NEArgumentSet;
	class NEArgumentInterfaceBase
	{
	private:
		friend class NEArgumentSet;
		virtual type_result _onInsertedInArguments(type_index index, NEArgumentSet& rhs) = 0;

	public:
		bool operator==(const NEArgumentInterfaceBase& rhs) const
		{
			return this == &rhs;
		}
	};

	template
	class NE_DLL NEListTemplate<NEArgumentInterfaceBase*, false>;
	typedef NEListTemplate<NEArgumentInterfaceBase*, false> NEArgumentInterfaceList;
}