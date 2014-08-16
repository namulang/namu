#include "Core.hpp"

namespace LG
{
	HANDLE NE_DLL Core::output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	type_ushort NE_DLL Core::max_width = Core::getMaxCursorPosition().X;
	type_ushort NE_DLL Core::max_height = Core::getMaxCursorPosition().Y;
	WindowList NE_DLL Core::windows;
	bool NE_DLL Core::color_lock = false;
}