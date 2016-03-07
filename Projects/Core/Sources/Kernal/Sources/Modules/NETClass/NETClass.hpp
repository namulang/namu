#pragma once

#include "../NETInterface/NETInterface.hpp"

namespace NE
{
	template <typename T>
	class NETClass : public NETInterface<T>
	{
		//	Declarations:
	public:
		typedef NETClass<T> This;
		typedef NETInterface<T> Super;
		typedef T Trait;
		typedef typename Trait::Super SuperTrait;
		typedef NETInterface<SuperTrait> SuperClass;

		//	Constructors:
	public:
		NETClass();
		NETClass(const NETClass& source);

		//	Destructors:
	public:
		virtual ~NETClass();

		//	Interfaces:
		//		Virtuals:
		//			NETInterface:
	public:
		virtual type_bool isInstantiatable() const;
		//			NEObject:
	public:
		virtual NEObject& instantiate() const;
	};
}

#include "NETClass.inl"