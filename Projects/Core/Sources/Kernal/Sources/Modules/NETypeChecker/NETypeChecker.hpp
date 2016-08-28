#pragma once

#pragma message("NETypeChecker.hpp - 1")
#include "../NETClass/define/ClassMacro.hpp"

namespace NE
{
	class NE_DLL NEAdam;

	class NETypeChecker
	{
		//	declared as Interface 'cause it can be instantiated. 
		//	not kind of NEObject.
		NE_DECLARE_INTERFACE_ONLY(NETypeChecker, NEAdam)

	public:
		typedef type_char no;
		typedef type_short yes;
	};
}
#pragma message("NETypeChecker.hpp - 3")