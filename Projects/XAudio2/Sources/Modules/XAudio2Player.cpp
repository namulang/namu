#include "XAudio2Player.hpp"
#include "XAudio2Manager.hpp"

namespace XA2
{
	type_result XAudio2Player::play(type_count loop_count)
	{
		//	pre:
		if (loop_count <= 0) return RESULT_SUCCESS;
		type_result result = RESULT_SUCCESS;
		XAudio2Manager& mng = XAudio2Manager::getInstance();
		//		Decoder È¹µæ:
		XAudio2Decoder& decoder = getDecoder();
		if (!&decoder || !decoder.arg_load_success.getValue())
			return RESULT_TYPE_WARNING;
		if(_is_paused)
			_real_channel->Start();
		else
			result = mng.play(*this, loop_count);

		arg_play_command.setValue(loop_count-1);
		_is_paused = false;
		return result;
	}
	type_result XAudio2Player::stop()
	{
		if (!_real_channel) return RESULT_SUCCESS;

		_real_channel->Stop();
		_real_channel->DestroyVoice();
		_real_channel = 0x00;
		_is_paused = false;
		return RESULT_SUCCESS;
	}
	bool XAudio2Player::isStopped() const
	{
		if( ! _real_channel) return true;

		return XAudio2Manager::getInstance().isStopped(*_real_channel);
	}
	type_result XAudio2Player::pause()
	{
		if (!_real_channel) return RESULT_TYPE_WARNING;

		arg_play_command.setValue(0);
		_is_paused = true;
		_real_channel->Stop();
		return RESULT_SUCCESS;
	}
	type_result XAudio2Player::_onExecute()
	{
		if( ! isEnable()) return RESULT_SUCCESS;

		if(arg_volume.isEnable())
		{
			if (arg_volume.getPurpose() == NEArgumentBase::WRITTEN)
				arg_volume.setValue(getVolume());
			else
				_real_channel->SetVolume(arg_volume.getValue());
		}			

		if (arg_play_command.isEnable())
		{
			type_int command = arg_play_command.getValue();
			type_result result = RESULT_SUCCESS;
			switch (command)
			{
			case -1:	return pause();
			case -2:	return stop();
			default:
				if (command > 0)
					result = play(arg_play_command.getValue());
			}
		}	

		return RESULT_SUCCESS;
	}
}