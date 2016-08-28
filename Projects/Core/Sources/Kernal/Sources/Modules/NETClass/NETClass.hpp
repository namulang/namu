#pragma once

#pragma message("NETClass.hpp - 1")
#include "NETClass.inl"
#pragma message("NETClass.hpp - 2")
#include "../NETInterface/NETInterface.hpp"
#pragma message("NETClass.hpp - 3")
#include "../NETConcreteClass/NETConcreteClass.hpp"
#pragma message("NETClass.hpp - 4")
#include "../NETUnknownMetaClass/NETUnknownMetaClass.hpp"

namespace NE
{
	//	Why this file is need to be created:
	//		Currently, we've met the situation needing forward-declaration at 
	//		template classes which are part of RTTI component.
	//		So, it's very important to distinguish implementation and declaration
	//		of class templates.
	//		
	//		eventually, NETClass.inl file will be included to who have to declare
	//		class template, not define implementation.
}