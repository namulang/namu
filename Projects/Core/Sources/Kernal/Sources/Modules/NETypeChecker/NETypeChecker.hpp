#pragma once

#include "../../Includes/Includes.hpp"
#include "../NETClass/define/ClassMacro.hpp"

namespace NE
{
	template <typename T>
	class NETClass;

	class NE_DLL NEClassBase;

	class NE_DLL NETypeChecker
	{
		//	declared as Interface 'cause it can be instantiated. 
		//	not kind of NEObject.
		NE_DECLARE_INTERFACE(NETypeChecker, NEAdam)

	public:
		typedef NETypeChecker This;
		typedef NETInterface<This> MetaClass;
	public:
		static NEClassBase& getClassStatically();		

	public:
		typedef type_char no;
		typedef type_short yes;
	};
}