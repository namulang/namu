#pragma once

#include "../Resource/Resource.hpp"

namespace DX9Graphics
{
	class Model;

	class NE_DLL DockableResource : public Resource
	{
	public:
		typedef Resource SuperClass;
		typedef DockableResource ThisClass;

	public:
		virtual type_result dock(Model& model)
		{
			return RESULT_SUCCESS;
		}
	};	
}