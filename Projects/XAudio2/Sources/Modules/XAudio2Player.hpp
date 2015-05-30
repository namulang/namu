#pragma once

#include "Channels.hpp"
#include "XAudio2Mixer.hpp"
#include "XAudio2Decoder.hpp"

namespace XA2
{
	using namespace NE;

	class NE_DLL XAudio2Player : public XAudio2Mixer
	{
	public:
		typedef XAudio2Player ThisClass;
		typedef XAudio2Mixer SuperClass;
		friend class XAudio2Manager;

	public:
		NETArgument<NEModuleSelector>	arg_decoder;
		NETArgument<NEModuleSelector>	arg_mixer;
		NETArgument<NEIntKey>			arg_play_command;	//	0: Pause, -1: Stop, 앙수: 재생횟수

	public:
		XAudio2Decoder& getDecoder() 
		{
			return _cast<XAudio2Decoder>(arg_decoder);
		}
		XAudio2Mixer& getMixer()
		{
			return _cast<XAudio2Mixer>(arg_mixer);
		}
		type_result play(type_count loop_count);
		type_result stop();
		type_result pause();
		bool isStopped() const;
		virtual type_result setVolume(type_float new_volume)
		{
			if (!_real_channel && _real_channel->voice)
				return RESULT_TYPE_WARNING;

			_real_channel->voice->SetVolume(new_volume);

			return arg_volume.setValue(new_volume);
		}
		virtual type_float getVolume() const
		{
			if( ! _real_channel && _real_channel->voice)
				return RESULT_TYPE_WARNING;

			type_float to_return = 0.0f;
			_real_channel->voice->GetVolume(&to_return);

			return to_return;
		}
		Channel& getRealChannel()
		{
			return *_real_channel;
		}
		const Channel& getRealChannel() const
		{
			return *_real_channel;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if(NEResult::hasError(_header.isValid()))
			{
				_header.getName() = "XAudio2Player";
				_header.getDeveloper() = "kniz";
				_header.setRevision(1);
				_header.getVersion() = "0.0.1a";
				_header.getReleaseDate() = "2015-05-06";
				_header.getComment() =
					"디코딩된 PCM 데이터를 재생하는 플레이어입니다.\n"
					"재생, 일시정지, 정지를 할 수 있으며, 이를 사용하기 위해서는 디코더가 필요합니다.\n"
					"Command가 한번 Execute 되면, 0(아무것도 안함)으로 Set 됩니다.\n"
					"이미 Playing 인 Player에게 다시 Play를 명령을 내리면, 기존의 재생중인 사운드의 제어권을 잃고, 별개로 새로운 채널을 열어서 재생합니다."
					"결과적으로 같은 사운드 2개가 동시에 들리게 되며 이전에 재생한 소리는 제어할 수 없습니다.\n";
				"믹서를 지정하지 않은 경우는 바로 마스터믹서로 라우팅 됩니다.\n";

				NETStringSet& argcomments = _header.getArgumentsComments();
				argcomments.create(4);				
				argcomments.push("Decoder\n소리 정보를 담고 있는 디코더 1개를 여기에 연결합니다.");
				argcomments.push("Mixer\n별도의 믹서로 라우팅하려면 여기에 믹서를 1개 연결합니다.");
				argcomments.push("PlayCommand\n-3:멈춤\t-2: 일시정지\t-1: 무한 재생\t0: 아무것도 안함\n양수: 재생 횟수. 이후 0으로 Set 됩니다.");
				argcomments.push(SuperClass::getHeader().getArgumentsComments()[0]);				
			}

			return _header;
		}

	protected:
		virtual type_result _onFetchModule()
		{
			SuperClass::_onFetchModule();

			_real_channel = 0;
			_is_paused = false;
			arg_mixer.setEnable(false);
			arg_decoder.setPurposeLimitation(NEArgumentBase::READ_BY);			
			arg_play_command.setValue(1);
			arg_play_command.setPurposeLimitation(NEArgumentBase::READ_BY);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_decoder);
			tray.push(arg_mixer);
			tray.push(arg_play_command);

			SuperClass::_onFetchArguments(tray);

			return RESULT_SUCCESS;
		}
		virtual type_result _onExecute();

	private:
		template <typename T>
		static T& _cast(NEModule& target)
		{
			const NECodeSet& cs = T::getModuleScriptCodes();
			T* nullpointer = 0x00;

			NECode sample(target.getScriptCode(), NECodeType(NECodeType::MODULE_SCRIPT));

			if (&target								&&
				cs.find(sample) != NE_INDEX_ERROR)
				return static_cast<T&>(target);

			return *nullpointer;
		}

		template <typename T>
		static T& _cast(NETArgument<NEModuleSelector>& target)
		{
			T* nullpointer = 0x00;
			NEModule& module = target.getValue().getModule();
			if (!&module) return *nullpointer;

			target.getValue().initializeReferingPoint();

			return _cast<T>(module);
		}

	private:
		Channel* _real_channel;
		bool _is_paused;
	};
}