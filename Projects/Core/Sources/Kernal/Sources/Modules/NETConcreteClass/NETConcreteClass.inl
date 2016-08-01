#pragma once

#include "../NETClassBase/NETClassBase.inl"

namespace NE
{
	template <typename T>
	class NETConcreteClass : public NETClassBase<T>
	{
		//	Declarations:
	public:
		typedef NETConcreteClass<T> This;
		typedef NETClassBase<T> Super;

		//	Constructors:
	public:
		NETConcreteClass();
		NETConcreteClass(const NETConcreteClass& source);

		//	Destructors:
	public:
		virtual ~NETConcreteClass();

		//	Interfaces:
		//		Virtuals:
		//			NEClassBase:
	public:
		virtual NEObject& instantiate() const;
		//			NEObject:
	public:
		virtual NEObject& clone() const;

	};
}