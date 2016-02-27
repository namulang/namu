#pragma once

#include "../Includes/Includes.hpp"
#include <XAudio2.h>

namespace XA2
{
	using namespace NE;

	class XAudio2Decoder;

	struct Channel : public NEObject
	{
		IXAudio2SourceVoice* voice;
		XAudio2Decoder*		decoder;

		Channel() : voice(0), decoder(0) {}
		Channel(const Channel& rhs) 
			: voice(rhs.voice), decoder(rhs.decoder) {}		

	public:
		bool operator==(const Channel& rhs) const
		{
			return voice == rhs.voice && decoder == rhs.decoder;
		}
		bool operator!=(const Channel& rhs) const
		{
			return ! operator==(rhs);
		}
		bool isStopped() const
		{
			if( ! voice) return true;

			XAUDIO2_VOICE_STATE state;
			voice->GetState(&state);

			if (state.BuffersQueued > 0)
				return false;
			else
				return true;
		}
		virtual NEObject& clone() const
		{
			return *(new Channel(*this));
		}
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
		{
			return saver;
		}
		type_result isValid() const
		{
			return RESULT_SUCCESS;
		}
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
		{
			return loader;
		}
		virtual void release()
		{
			if(voice)
			{
				voice->Stop();
				voice->DestroyVoice();
			}
			voice = 0;
			decoder = 0;
		}
	};	

	template
	class NE_DLL NETArray<Channel, false>;
	typedef NETArray<Channel, false> Channels;
}