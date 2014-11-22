#pragma once

#include "../../Interfaces/NEUpdatable/NEUpdatable.hpp"

namespace NE
{
	class NE_DLL NEUpdatable
	{
	public:
		virtual type_result update() = 0;
	};
}