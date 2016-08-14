#pragma once

#include "../../Includes/Includes.hpp"
#include "../NEAdam/NEAdam.hpp"

namespace NE
{
	class NE_DLL NETypeChecker
	{
		//	declared as Interface 'cause it can be instantiated. 
		//	not kind of NEObject.
		NE_DECLARE_INTERFACE(NETypeChecker, NEAdam)

	public:
		static NEClassBase& getClassStatically();		

	public:
		typedef type_char no;
		typedef type_short yes;
	};
}