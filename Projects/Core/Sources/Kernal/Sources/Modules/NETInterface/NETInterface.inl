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
		NE_DECLARE_CLASS_ONLY(NETInterface<T>, NETClassBase<T>)

		//	Constructors:
	public:
		NETInterface();
		NETInterface(const This& source);

		//	Destructors:
	public:
		virtual ~NETInterface();

		//	Inherited:
		//		NEClassBase:
	public:
		virtual NEObject& instantiate() const;
	};
}