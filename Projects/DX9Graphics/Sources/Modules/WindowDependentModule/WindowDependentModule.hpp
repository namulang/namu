#pragma once

#include "../../Commons/Templates/DependentModuleTemplate/DependentModuleTemplate.hpp"
#include "../../Includes/Includes.hpp"

namespace DX9Graphics
{
	template
	class NE_DLL DependentModuleTemplate<NE::Window>;
	typedef DependentModuleTemplate<NE::Window> WindowDependentModule;
}