#pragma once

#include "../../Includes/Includes.hpp"
#include "../NETClass/define/ClassMacro.hpp"

namespace NE
{
	template <typename T>
	class NETClass;
	template <typename T>
	class NETInterface;

	class NE_DLL NETypeChecker
	{
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