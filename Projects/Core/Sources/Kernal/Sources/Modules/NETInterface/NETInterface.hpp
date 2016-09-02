#pragma once

#pragma message("NETInterface.hpp - 1")
#include "NETInterface.inl"
#pragma message("NETInterface.hpp - 2")
#include "../NETClassBase/NETClassBase.hpp"
#pragma message("NETInterface.hpp - 3")

namespace NE
{
	//	NETClass doesn't need to declare MetaClass Macro (like NE_DEFINE_CLASS_ONLY...):
	//		its class definitions are inherited from NETClassBase.
}