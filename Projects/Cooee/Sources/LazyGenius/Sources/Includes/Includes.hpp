#pragma once

#include <iostream>
#include <conio.h>
#include <iomanip>
#include <Windows.h>

#include <Macro/Sources/Modules/DLLMacro/SetDLLIMPORT.hpp>
// @юс╫ц:
#ifdef DEVELOPER
#	undef DEVELOPER
#endif
#define DEVELOPER
#include <Kernal/Sources/EntryPoints/Headers.hpp>
#ifdef LAZYGENIUSFRAMEWORK_EXPORTS
#	include <Macro/Sources/Modules/DLLMacro/SetDLLEXPORT.hpp>
#endif