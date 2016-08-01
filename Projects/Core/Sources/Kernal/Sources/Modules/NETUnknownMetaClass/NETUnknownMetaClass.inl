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
		//	Declarations:
	public:
		typedef NETUnknownMetaClass<T> This;
		typedef NETClassBase<T> Super;

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
		//				NEObject:
	public:
		virtual NEObject& clone() const;
	};
}