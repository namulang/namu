#pragma once

#include "../../Includes/Includes.hpp"

namespace DX9Graphics
{
	class NE_DLL Renderable
	{
	public:
		virtual type_result render() = 0;
	};
}