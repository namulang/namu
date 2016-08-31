//	---------------------------------------------------------------------------------
//	Name			:	NETInterface
//	Comments		:	
//	Releationships	:
//	Charateristics	:	
//	Usage			:	
//	Memo			:	
//	Author			:	2016-02-13	kniz	Creations
//	---------------------------------------------------------------------------------
#pragma once

#pragma message("NETInterface.inl - 1")
#include "../NETClassBase/NETClassBase.inl"
#pragma message("NETInterface.inl - 2")

namespace NE
{
	template <typename T>
	class NETInterface : public NETClassBase<T>
	{
		//	NETClass doesn't need to declare MetaClass Macro (like NE_DEFINE_CLASS_ONLY...):
		//		its class definitions are inherited from NETClassBase.
	};
}