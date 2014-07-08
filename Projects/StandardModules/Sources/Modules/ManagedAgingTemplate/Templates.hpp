#pragma once

#include "ManagedAgingTemplate.hpp"

namespace NE
{
	template
	class NE_DLL ManagedAgingTemplate<type_float, NEType::NEFLOAT_KEY>;
	typedef ManagedAgingTemplate<type_float, NEType::NEFLOAT_KEY> ManagedFloatAging;
}