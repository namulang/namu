#pragma once

#include "XAudio2Player.hpp"

namespace XA2
{
	class NE_DLL XAudio2Manager
	{
	public:
		typedef XAudio2Manager ThisClass;
		const int DEFAULT_CHANNEL_SIZE = 32;

	private:
		XAudio2Manager()
			: _xa2(0), _master_mixer(0)
		{
			_channels.create(DEFAULT_CHANNEL_SIZE);
		}
		XAudio2Manager(const ThisClass& rhs) 
			: _xa2(0), _master_mixer(0)
		{

		}

	public:
		IXAudio2& getXAudio2()
		{
			return *_xa2;
		}
		const IXAudio2& getXAudio2() const
		{
			return *_xa2;
		}
		IXAudio2MasteringVoice& getRealMasterMixer()
		{
			return *_master_mixer;
		}
		const IXAudio2MasteringVoice& getRealMasterMixer() const
		{
			return *_master_mixer;
		}
		Channels& getChannels() 
		{
			return _channels;
		}
		const Channels& getChannels() const
		{
			return _channels;
		}

	public:
		type_result play(XAudio2Player& player, type_count loop_count)
		{
			//	decoder 획득:
			XAudio2Decoder& decoder = player.getDecoder();
			if( ! &decoder) return RESULT_TYPE_WARNING;
			//	mixer 존재하는가:
			XAUDIO2_SEND_DESCRIPTOR send = {0, /*pointer of Mixer*/0};
			XAUDIO2_VOICE_SENDS sendlist = {1, &send};
			XAUDIO2_VOICE_SENDS* sendlist_ptr = 0;
			XAudio2Mixer& mixer = player.getMixer();
			//		존재하면 SendList 생성:
			if (&mixer && &mixer.getRealMixer())
			{
				send.pOutputVoice = &mixer.getRealMixer();
				sendlist_ptr = &sendlist;
			}

			//	채널이 비어있다면 push:
			type_index trg_n = -1;
			for (int n = 0; n < _channels.getLength(); n++)
				if (!&_channels[n] || isStopped(_channels[n]))
				{
					trg_n = n;
					break;
				}
				if(trg_n == -1)
					return ALERT_WARNING_IN_SPECIFIED_MODULE(NEExportable::Identifier("XAudio2Player.kniz")," : 비어있는 채널을 찾지 못했습니다. 재생을 중지합니다.");
				//	해당 채널 Flush:
				if (player._real_channel = &_channels[trg_n])
				{
					player._real_channel->Stop();
					player._real_channel->DestroyVoice();
					player._real_channel = 0;
				}

				if(FAILED(_xa2->CreateSourceVoice(&player._real_channel, &decoder.getWaveFormatEX(), 0, XAUDIO2_DEFAULT_FREQ_RATIO, NULL, sendlist_ptr, NULL)))
					return ALERT_ERROR_IN_SPECIFIED_MODULE(NEExportable::Identifier("XAudio2Player.kniz"),
					"경고XX:\t효과음소스보이스를 생성하지 못했습니다. 음악이 재생되지 않습니다. 파일명: %s", decoder.arg_filepath.getValue().toCharPointer());
				//	TempBuffer 생성:
				XAUDIO2_BUFFER buf = {0, };
				buf.pAudioData = decoder.getWaveData();
				buf.Flags = XAUDIO2_END_OF_STREAM; // let source-voice know not to expect any data will be followed after this.
				buf.AudioBytes = decoder.arg_raw_pcm_size.getValue();
				buf.LoopCount = loop_count;

				//	TempBuffer Submit:
				if(FAILED(player._real_channel->SubmitSourceBuffer(&buf)))
				{
					return ALERT_ERROR_IN_SPECIFIED_MODULE(NEExportable::Identifier("XAudio2Player.kniz"),
						": SourceVoice 버퍼에 디코딩된 PCM데이터를 Submit 하지 못했습니다.");
					player._real_channel->Stop();
					player._real_channel->DestroyVoice();
					player._real_channel = 0;
				}

				//	Start:
				player._real_channel->Start();

				return RESULT_SUCCESS;

		}

	public:
		bool isStopped(Channel& channel) const
		{
			if( ! &channel) return true;

			XAUDIO2_VOICE_STATE state;
			channel.GetState(&state);

			if (state.BuffersQueued > 0)
				return false;
			else
				return true;
		}
		void initialize()
		{
			_initializeXAudio2();
			_initializeMasteringVoice();
			_initializeChannels();
		}
		void release()
		{
			_releaseChannels();
			if (_master_mixer)
				_master_mixer->DestroyVoice();
			_master_mixer = 0;
			if (_xa2)
				_xa2->Release();
			_xa2 = 0;
		}

	private:
		void _initializeXAudio2()
		{
			CoInitializeEx(NULL, COINIT_MULTITHREADED);

#ifdef _DEBUG
#	define DEBUG_OR_NOT XAUDIO2_DEBUG_ENGINE
#else
#	define DEBUG_OR_NOT 0
#endif
			if (FAILED(XAudio2Create(&_xa2, DEBUG_OR_NOT)))
			{
				ALERT_ERROR_IN_SPECIFIED_MODULE(NEExportable::Identifier("XAudio2Player.kniz"),
					"경고XX:\tXAudio2 초기화 실패. 소리가 나오지 않습니다.");
				release();
			}
		}
		void _initializeMasteringVoice()
		{
			if( !_xa2) return;
			if(FAILED(_xa2->CreateMasteringVoice(&_master_mixer)))
			{
				ALERT_ERROR_IN_SPECIFIED_MODULE(NEExportable::Identifier("XAudio2Player.kniz"),
					"경고XX:\t마스터링 보이스 초기화 실패. 소리가 나오지 않습니다.");

				release();
			}
		}
		void _releaseChannels()
		{
			while(_channels.getLength() > 0)
			{
				Channel& ch = _channels[_channels.getLengthLastIndex()];
				if( ! &ch) continue;

				ch.Stop();
				ch.DestroyVoice();

				_channels.pop();
			}
		}
		void _initializeChannels()
		{
			_releaseChannels();

			for (int n = 0; n < DEFAULT_CHANNEL_SIZE; n++)
				_channels.push(0);
		}

	private:
		Channels				_channels;
		IXAudio2*				_xa2;
		IXAudio2MasteringVoice*	_master_mixer;

	public:
		static ThisClass& getInstance()
		{
			static ThisClass _global;

			if (!_global._xa2)
				_global.initialize();

			return _global;
		}
	};
}