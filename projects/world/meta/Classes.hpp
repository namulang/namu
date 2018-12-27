#pragma once

#include "../container/TArray.hpp"
#include "Class.hpp"

namespace wrd
{
	class Classes : public TArray<Class>
	{	WRD_CLASS(Classes, TArray<Class>)
	public:
	};
}
