#pragma once

#include "../NETInterface/NETInterface.hpp"

namespace NE
{
	template <typename T>
	class NETConcreteClass : public NETInterface<T>
	{
		//	Declarations:
	public:
		typedef NETConcreteClass<T> This;
		typedef NETInterface<T> Super;
		typedef NETConcreteClass<NEConcreteClass> MetaClass;
		typedef T Trait;
		typedef typename Trait::Super SuperTrait;
		typedef NETInterface<SuperTrait> SuperClass;

		//	Constructors:
	public:
		NETConcreteClass();
		NETConcreteClass(const NETConcreteClass& source);

		//	Destructors:
	public:
		virtual ~NETConcreteClass();

		//	Interfaces:
		//		Virtuals:
		//			NEObject:
	public:
		virtual const NEClassBase& getClass() const;
		virtual NEObject& instantiate() const;

	public:
		static const NEClassBase& getClassStatically();
	};

	template <typename T>
	const NEClassBase& NE::NETConcreteClass<T>::getClass() const
	{
		
	}

}

#include "NETConcreteClass.inl"
#include "Specialization.inl"