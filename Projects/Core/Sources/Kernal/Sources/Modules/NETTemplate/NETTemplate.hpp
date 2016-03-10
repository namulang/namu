#pragma once

#include "../NEClassBase/NEClassBase.hpp"

namespace NE
{
	template <typename T>
	class NETTemplate : public NEClassBase
	{
	public:
		typedef NETTemplate<T> This;
		typedef This ThisClass;
		
	};
}