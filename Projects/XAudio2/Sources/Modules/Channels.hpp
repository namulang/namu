#pragma once

#include "../Includes/Includes.hpp"
#include <XAudio2.h>

namespace XA2
{
	using namespace NE;

	typedef IXAudio2SourceVoice Channel;

	template
	class NE_DLL NEArrayTemplate<Channel*, false>;
	typedef NEArrayTemplate<Channel*, false> Channels;
}