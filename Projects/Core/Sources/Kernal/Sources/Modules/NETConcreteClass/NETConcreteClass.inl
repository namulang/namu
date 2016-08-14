#pragma once

#include "../NETClassBase/NETClassBase.inl"

namespace NE
{
	template <typename T>
	class NETConcreteClass : public NETClassBase<T>
	{
		NE_DECLARE_CLASS_ONLY(NETConcreteClass<T>, NETClassBase<T>)

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