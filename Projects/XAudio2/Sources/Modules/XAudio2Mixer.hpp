#pragma once

#include "Channels.hpp"

namespace XA2
{
	typedef IXAudio2Voice Mixer;

	class NE_DLL XAudio2Mixer : public NEModule
	{
	public:
		typedef XAudio2Mixer ThisClass;
		typedef NEModule SuperClass;

	public:
		XAudio2Mixer()
			: SuperClass(), _real_channel(0)
		{

		}
		XAudio2Mixer(const ThisClass& source)
			: SuperClass(source), _real_channel(0), arg_volume(source.arg_volume)
		{

		}
		virtual ~XAudio2Mixer()
		{
			_release();
		}

	public:
		mutable NETArgument<NEFloatKey>	arg_volume;

	public:
		Mixer& getRealMixer()
		{
			return *_real_channel;
		}
		const Mixer& getRealMixer() const
		{
			return *_real_channel;
		}
		virtual type_result setVolume(type_float new_volume)
		{
			if (!_real_channel)
				return RESULT_TYPE_WARNING;

			_real_channel->SetVolume(new_volume);

			return arg_volume.setValue(new_volume);
		}
		virtual type_float getVolume() const
		{
			if (!_real_channel)
				return RESULT_TYPE_WARNING;

			type_float volume = 0.0f;
			_real_channel->GetVolume(&volume);
			if(	arg_volume.getPurpose() == NEArgumentBase::WRITTEN	&&
				arg_volume.isEnable()								) 
				arg_volume.setValue(volume);
			return volume;
		}

	public:
		virtual void release() 
		{
			SuperClass::release();

			_release();
		}
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if (NEResult::hasError(_header.isValid()))
			{
				_header.getName() = "XAudio2Mixer";
				_header.getDeveloper() = "kniz";
				_header.setRevision(1);
				_header.getVersion() = "0.0.1a";
				_header.getReleaseDate() = "2015-05-06";
				_header.getComment() = "XAudio2Player 들로부터 전달된 소리데이터에 대한 믹서입니다.";
				NETStringSet& argcomments = _header.getArgumentsComments();
				argcomments.create(1);
				argcomments.push("Volume\nREAD로 하면 Key의 값을 읽어서 볼륨을 Set합니다.\nWRITE로 하면 현재의 볼륨을 Get해서 Key에 WRITE 합니다.");
			}

			return _header;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	protected:
		virtual type_result _onFetchModule()
		{
			arg_volume.setDefault(1.0f);
			arg_volume.setPurposeLimitation(NEArgumentBase::READ_OR_WRITTEN);
			arg_volume.setPurpose(NEArgumentBase::READ_BY);
			arg_volume.setEnable(false);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_volume);

			return RESULT_SUCCESS;
		}
		virtual type_result _onExecute()
		{
			if( ! _real_channel)
				_initializeRealMixer();

			return RESULT_SUCCESS;
		}

	private:
		void _initializeRealMixer();
		void _release()
		{
			if (_real_channel)
				_real_channel->DestroyVoice();

			_real_channel = 0x00;
		}

	private:
		IXAudio2SourceVoice* _real_channel;

	public:
		static const NECodeSet& getModuleScriptCodes();
	};
}