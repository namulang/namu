#pragma once

#include "../NETClassBase/NETClassBase.inl"

namespace NE
{
	template <typename T>
	class NETConcreteClass : public NETClassBase<T>
	{
		//	NETClass doesn't need to declare MetaClass Macro (like NE_DEFINE_CLASS_ONLY...):
		//		its class definitions are inherited from NETClassBase.
		
		//	Constructors:
	public:
		NETConcreteClass();
		NETConcreteClass(const This& source);

		//	Destructors:
	public:
		virtual ~NETConcreteClass();

		//	Interfaces:
		//		Virtuals:
		//			NEClassBase:
	public:
		virtual NEObject& instantiate() const;
	};
}