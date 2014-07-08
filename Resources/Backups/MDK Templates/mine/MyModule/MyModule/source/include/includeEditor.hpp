#pragma once

#include <Macro/source/module/DLLMacro/SetDLLIMPORT.hpp>

#if PROPERTY_INCLUDE_EDITOR == 1
#	include <Editor/source/main/header.hpp>
#endif

#ifdef MyModule_EXPORTS
#	include <Macro/source/module/DLLMacro/SetDLLEXPORT.hpp>
#endif
