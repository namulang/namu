#include "BlurProgram.hpp"
#include "blur_hlsl.hpp"

namespace DX9Graphics
{
	LPCVOID BlurProgram::_onRequestShaderCode(OUT type_int& size_of_binary) const
	{		
		size_of_binary = sizeof(g_main);

		return g_main;
	}
}