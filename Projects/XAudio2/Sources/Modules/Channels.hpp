#pragma once

#include "../Includes/Includes.hpp"
#include <XAudio2.h>

namespace XA2
{
	template
	class NE_DLL NEArrayTemplate<IXAudio2SourceVoice*, false>;
	typedef NEArrayTemplate<IXAudio2SourceVoice*, false> Channels;
}