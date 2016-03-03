#pragma once

#include "../NETInterface/NETInterface.hpp"

namespace NE
{
	template <typename T>
	class NETClass : public NETInterface
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
		NETInterface();
		NETInterface(const NETInterface& source);

		//	Destructors:
	public:
		virtual ~NETInterface();

		//	Interfaces:
		//		Virtuals:
	};
}