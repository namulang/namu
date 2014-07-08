#pragma once

#include "../common/Property.hpp"
#include <Macro/source/module/DLLMacro/SetDLLIMPORT.hpp>

#if PROPERTY_INCLUDE_KERNAL == 1
#	include <Kernal/source/main/header.hpp>
#endif

#ifdef Project1_EXPORTS
#	include <Macro/source/module/DLLMacro/SetDLLEXPORT.hpp>
#endif
