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

#include "../NETClassBase/NETClassBase.inl"

namespace NE
{
	template <typename T>
	class NETInterface : public NETClassBase<T>
	{
		//	Declarations:
	public:
		typedef NETInterface<T> This;
		typedef NETClassBase<T> Super;
		//	Constructors:
	public:
		NETInterface();
		NETInterface(const NETInterface& source);

		//	Destructors:
	public:
		virtual ~NETInterface();

		//	Inherited:
		//		NEClassBase:
	public:
		virtual NEObject& instantiate() const;
		//				NEObject:
	public:
		virtual NEObject& clone() const;
	};
}