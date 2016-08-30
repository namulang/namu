//	---------------------------------------------------------------------------------
//	Name			:	NETUnknownMetaClass
//	Comments		:	
//	Releationships	:
//	Charateristics	:	
//	Usage			:	
//	Memo			:	
//	Author			:	2016-02-13	kniz	Creations
//	---------------------------------------------------------------------------------
#pragma once

#include "../NETClassBase/NETClassBase.inl"

namespace NE
{
	template <typename T>
	class NETUnknownMetaClass : public NETClassBase<T>
	{
		//	NETClass doesn't need to declare MetaClass Macro (like NE_DEFINE_CLASS_ONLY...):
		//		its class definitions are inherited from NETClassBase.

		//	Constructors:
	public:
		NETUnknownMetaClass();
		NETUnknownMetaClass(const This& source);

		//	Destructors:
	public:
		virtual ~NETUnknownMetaClass();

		//	Inherited:
		//		NEClassBase:
	public:
		virtual NEObject& instantiate() const;
	};
}