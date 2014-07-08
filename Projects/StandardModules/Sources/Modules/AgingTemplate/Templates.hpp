#pragma once

#include "AgingTemplate.hpp"

namespace NE
{
	template
	class NE_DLL AgingTemplate<type_float, NEType::NEFLOAT_KEY>;
	typedef AgingTemplate<type_float, NEType::NEFLOAT_KEY> FloatAging;
}