#pragma once

#include "../NEModule/NEModule.hpp"
#include "../../Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<NEModule*, true, NEModule*, NEType::NEMODULESET>;
	typedef NEArrayTemplate<NEModule*, true, NEModule*, NEType::NEMODULESET> NEModuleSet;
}