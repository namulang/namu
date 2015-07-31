#include "XAudio2Player.hpp"
#include "XAudio2Manager.hpp"

namespace XA2
{
	type_result XAudio2Player::play(type_count loop_count)
	{
		//	pre:
		if (loop_count < 0) return RESULT_SUCCESS;
		type_result result = RESULT_SUCCESS;
		XAudio2Manager& mng = XAudio2Manager::getInstance();
		//		Decoder È¹µæ:
		XAudio2Decoder& decoder = getDecoder();
		if (!&decoder || !decoder.arg_load_success.getValue())
			return RESULT_TYPE_WARNING;
		if(_is_paused)
		{
			if(_real_channel && _real_channel->voice)
				_real_channel->voice->Start();
		}
		else
			result = mng.play(*this, loop_count);

		_is_paused = false;
		return result;
	}
	type_result XAudio2Player::stop()
	{
		if (!_real_channel) return RESULT_SUCCESS;

		_real_channel->release();
		_is_paused = false;
		return RESULT_SUCCESS;
	}
	bool XAudio2Player::isStopped() const
	{
		if( ! _real_channel) return true;

		return _real_channel->isStopped();
	}
	type_result XAudio2Player::pause()
	{
		arg_play_command.setValue(0);
		
		if (!_real_channel || ! _real_channel->voice) return RESULT_TYPE_WARNING;

		_is_paused = true;
		_real_channel->voice->Stop();
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
				if(_real_channel && _real_channel->voice)
					_real_channel->voice->SetVolume(arg_volume.getValue());
		}			

		if (arg_play_command.isEnable())
		{
			type_int command = arg_play_command.getValue();
			type_result result = RESULT_SUCCESS;
			switch (command)
			{
			case -3:	return stop();
			case -2:	return pause();
			case -1:	return play(1);
			default:
				if(command > 0)
				{
					result = play(arg_play_command.getValue()-1);
					arg_play_command.setValue(0);
				}
			}
		}	

		return RESULT_SUCCESS;
	}
}