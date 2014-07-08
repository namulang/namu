#pragma once

#include "../../Functions/NEResult/NEResult.hpp"

namespace NE
{
	class NE_DLL NEExecutable
	{
	public:
		virtual type_result execute() = 0;
	};
}