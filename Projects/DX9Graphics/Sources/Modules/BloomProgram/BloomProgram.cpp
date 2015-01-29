#include "BloomProgram.hpp"
#include "bloom_hlsl.hpp"

namespace DX9Graphics
{
	const float BloomProgram::DEFAULT_BLOOM_LEVEL = 0.35f;

	LPCVOID BloomProgram::_onRequestShaderCode(OUT type_int& size_of_binary) const
	{		
		size_of_binary = sizeof(g_main);

		return g_main;
	}
}