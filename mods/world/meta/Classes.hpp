#pragma once

#include "../containers/TArray.hpp"
#include "Class.hpp"

namespace wrd
{
	class Classes : public TArray<Class>
	{	WRD_CLASS_DECL(Classes, TArray<Class>)
	public:
	};
}
