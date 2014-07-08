#pragma once
#pragma comment(lib, "winmm.lib")
#include <MMSystem.h>

#include "CError.hpp"
#include <xaudio2.h>
#include <strsafe.h>
#include <conio.h>
#include "CAudioBuffer.hpp"

#ifdef	_DEBUG
#define DEFAULT_CAUDIO_INTIALIZE_XAUDIO_FLAG	XAUDIO2_DEBUG_ENGINE
#else
#define DEFAULT_CAUDIO_INTIALIZE_XAUDIO_FLAG	0
#endif
class CAudio
{
//멤버함수:
public:
	//	생성자:
	CAudio(int fx_max_channel): _xaudio2(NULL), _mastering_voice(NULL), _fx_submix(NULL), _music_submix(NULL),
	_fx_file(NULL), _fx_bank_capacity(0), _fx_bank_size(0), _music_file(NULL), _music_bank_capacity(0), _music_bank_size(0),
	_fx_source(NULL), _music_source(NULL), _enable(false), _fx_max_channel(fx_max_channel)

	{		
		_enable = true; // 중간에 에러가 나면, 각 함수 내부에서 release가 호출되면서 자동으로 enable이 false가 됨
		initializeXAudio2();
		initializeMasteringVoice();
		initializeSubmixVoice();
		initializeSoundSource();
		initializeMusicBuffer();
	}	
	//	소멸자:
	~CAudio()
	{
		release();
	}
	void	pauseAudio()
	{
		//	예외상황처리:
		if (!_enable)
			return ;

		_xaudio2->StopEngine();
	}
	void	unpauseAudio()
	{
		//	예외상황처리:
		if (!_enable)
			return ;

		_xaudio2->StartEngine();
	}
	void	initializeSoundCapacity(int fx_bank_capacity)
	{
		//	예외상황처리:
		if (fx_bank_capacity < 1)
		{
			CError	e
			(
				_T("경고XX:\t효과음뱅크의 허용량(capacity)의 설정이 0보다 작거나 같습니다. 음악 파일을 추가하지 못하게됩니다."), 
				_T("해결방법"),
				_T(__FUNCTION__)
			);
			e.log();
			return ;
		}

		//	메인코드:
		_fx_bank_capacity = fx_bank_capacity;
		_fx_file = new CAudioBuffer[_fx_bank_capacity];
		_fx_bank_size = 0;
	}
	void	loadSound(CString filename)
	{
		//	예외상황처리:
		if (!_enable)
			return ;
		//	예외상황처리:
		if (_fx_bank_capacity <= _fx_bank_size)
		{
			CError	e
			(
				_T("경고XX:\t뮤직뱅크가 꽉 찼습니다. 음악을 추가하지 못했습니다."), 
				_T("해결방법"),
				_T(__FUNCTION__)
			);
			e.log();
			return ;
		}

		//	메인코드:
		_fx_file[_fx_bank_size].load(filename);
		_fx_bank_size++;	
	}
	void	playSound(int index)
	{
		//	예외상황처리:
		if (!_enable)
			return ;
		//	예외상황처리:
		if (index >= _fx_bank_size)
			return ;
		if (!_fx_file)
			return ;
		if (!_fx_file[index]._load_success)
			return ;

		XAUDIO2_SEND_DESCRIPTOR SFXSend = {0, _fx_submix};	
		XAUDIO2_VOICE_SENDS SFXSendList = {1, &SFXSend};
		HRESULT hr = NULL;
		int		target_index = -1;
		//	어떤 fx인덱스에 넣을 것인지 찾기.
		for (int n=0; n < _fx_max_channel ;n++)
		{
			if ( !isPlaying(&_fx_source[n]) )
			{
				target_index = n;
				break;
			}
		}
		if (target_index == -1) // 채널이 포화상태라, 더이상 효과음을 넣을 수 없음
			return ; 
		
		if (_fx_source[target_index])
		{
			_fx_source[target_index]->Stop();
			_fx_source[target_index]->DestroyVoice();
		}

		hr = _xaudio2->CreateSourceVoice( &_fx_source[target_index], _fx_file[index]._wave_format, 0, XAUDIO2_DEFAULT_FREQ_RATIO, NULL,	&SFXSendList, NULL);
		if( FAILED( hr ) )
		{
			CError	e
			(
				_T("경고XX:\t효과음소스보이스를 생성하지 못했습니다. 음악이 재생되지 않습니다. 파일명:" + _fx_file[index]._filename ), 
				_T("해결방법"),
				_T(__FUNCTION__)
			);
			e.log();
			if (_fx_source[target_index])
			{
				_fx_source[target_index]->DestroyVoice();
				_fx_source[target_index] = NULL; 
			}
		}

		XAUDIO2_BUFFER	temp_buffer = {0};
		temp_buffer.pAudioData = _fx_file[index]._wave_data;
		temp_buffer.Flags = XAUDIO2_END_OF_STREAM;  // tell the source voice not to expect any data after this buffer
		temp_buffer.AudioBytes = _fx_file[index]._wave_size;
		
		if( FAILED( _fx_source[target_index]->SubmitSourceBuffer( &temp_buffer ) ) )
		{
			CError	e
			(
				_T("경고XX:\t효과음소스버퍼를 SUBMIT 하지못했습니다. 음악이 재생되지 않습니다. 파일명:" + _fx_file[index]._filename), 
				_T("해결방법"),
				_T(__FUNCTION__)
			);
			_fx_source[target_index]->DestroyVoice();
			_fx_file[index].releaseWaveFormat();
			_fx_file[index].releaseWaveData();
			_fx_file[index]._load_success = false; // 매번 이부분까지 와서 실패하게 만들면, 부하가 만만치 않으므로, 일찌감치 버퍼를 삭제한다
		}
		_fx_source[target_index]->Start();
	}
	void	pauseSound()
	{
		//	예외상황처리:
		if (!_enable)
			return ;

		for (int n=0; n < _fx_max_channel ;n++)
		{
			if (_fx_source[n])
			{
				_fx_source[n]->Stop();
			}
		}
	}
	void	unpauseSound()
	{
		//	예외상황처리:
		if (!_enable)
			return ;
		
		for (int n=0; n < _fx_max_channel ;n++)
		{
			if (_fx_source[n])
			{
				_fx_source[n]->Start();
			}
		}
	}
	float	getSoundVolume()
	{
		//	예외상황처리:
		if (!_enable)
			return 0.0f;
		float	volume = 0.0f;
		_fx_submix->GetVolume(&volume);
		
		return volume;
	}
	void	setSoundVolume(float volume)
	{
		//	예외상황처리:
		if (!_enable)
			return ;

		_fx_submix->SetVolume(volume);
	}
	void	initializeMusicCapacity(int music_bank_capacity)
	{
		//	예외상황처리:
		if (music_bank_capacity < 1)
		{
			CError	e
			(
				_T("경고XX:\t뮤직뱅크의 허용량(capacity)의 설정이 0보다 작거나 같습니다. 음악 파일을 추가하지 못하게됩니다."), 
				_T("해결방법"),
				_T(__FUNCTION__)
			);
			e.log();
			return ;
		}

		//	메인코드:
		_music_bank_capacity = music_bank_capacity;
		_music_file = new CAudioBuffer[_music_bank_capacity];
		_music_bank_size = 0;
	}
	void	loadMusic(CString filename)
	{
		//	예외상황처리:
		if (!_enable)
			return ;
		//	예외상황처리:
		if (_music_bank_capacity <= _music_bank_size)
		{
			CError	e
			(
				_T("경고XX:\t뮤직뱅크가 꽉 찼습니다. 음악을 추가하지 못했습니다."), 
				_T("해결방법"),
				_T(__FUNCTION__)
			);
			e.log();
			return ;
		}

		//	메인코드:
		_music_file[_music_bank_size].load(filename);
		_music_bank_size++;		
	}
	void	playMusic(int index, DWORD loop_count = 0) // XAUDIO2_LOOP_INFINITE: infinity, 0: no looping
	{
		//	예외상황처리:
		if (!_enable)
			return ;
		//	예외상황처리:
		if (index > _music_bank_size)
			return ;
		if (!_music_file)
			return ;
		if (!_music_file[index]._load_success)
			return ;

		
		XAUDIO2_SEND_DESCRIPTOR SFXSend = {0, _music_submix};	
		XAUDIO2_VOICE_SENDS SFXSendList = {1, &SFXSend};
		HRESULT hr = NULL;

		if (_music_source)
		{
			_music_source->Stop();
			_music_source->DestroyVoice();
		}

		hr = _xaudio2->CreateSourceVoice( &_music_source, _music_file[index]._wave_format, 0, XAUDIO2_DEFAULT_FREQ_RATIO, NULL,	&SFXSendList, NULL);
		if( FAILED( hr ) )
		{
			CError	e
			(
				_T("경고XX:\t뮤직소스보이스를 생성하지 못했습니다. 음악이 재생되지 않습니다. 파일명:" + _music_file[index]._filename ), 
				_T("해결방법"),
				_T(__FUNCTION__)
			);
			e.log();
			if (_music_source) 
			{
				_music_source->DestroyVoice();
				_music_source = NULL;
			}

		}

		initializeMusicBuffer();
		_music_buffer.pAudioData = _music_file[index]._wave_data;
		_music_buffer.Flags = XAUDIO2_END_OF_STREAM;  // tell the source voice not to expect any data after this buffer
		_music_buffer.AudioBytes = _music_file[index]._wave_size;
		_music_buffer.LoopCount = loop_count;
		
		//buffer.PlayLength = pwfx->nSamplesPerSec * 2;
		if( FAILED( _music_source->SubmitSourceBuffer( &_music_buffer ) ) )
		{
			CError	e
			(
				_T("경고XX:\t뮤직소스버퍼를 SUBMIT 하지못했습니다. 음악이 재생되지 않습니다. 파일명:" + _music_file[index]._filename), 
				_T("해결방법"),
				_T(__FUNCTION__)
			);
			e.log();
			_music_source->DestroyVoice();
			_music_file[index].releaseWaveFormat();
			_music_file[index].releaseWaveData();
			_music_file[index]._load_success = false; // 매번 이부분까지 와서 실패하게 만들면, 부하가 만만치 않으므로, 일찌감치 버퍼를 삭제한다
		}
		_music_source->Start();
	}
	void	pauseMusic()
	{
		//	예외상황처리:
		if (!_enable)
			return ;
		if (!_music_source)
			return ;

		_music_source->Stop();
	}
	void	unpauseMusic()
	{
		//	예외상황처리:
		if (!_enable)
			return ;
		if (!_music_source)
			return ;

		_music_source->Start();
	}
	void	replayMusic()
	{
		//	예외상황처리:
		if (!_enable)
			return ;
		if (!_music_source)
			return ;

		if ( isPlaying(&_music_source) )
			_music_source->Stop();
		_music_source->FlushSourceBuffers();
		_music_buffer.PlayBegin = 0;
		_music_source->SubmitSourceBuffer(&_music_buffer);
		_music_source->Start();
	}
	float	getMusicVolume()
	{	//	예외상황처리:
		if (!_enable)
			return 0.0f;

		float	volume;
		_music_submix->GetVolume(&volume);
		
		return volume;
	}
	void	setMusicVolume(float volume)
	{
		//	예외상황처리:
		if (!_enable)
			return ;

		_music_submix->SetVolume(volume);
	}
	bool	isPlaying(IXAudio2SourceVoice** source_voice)
	{
		//	예외상황처리:
		if (!_enable)
			return false;
		if (!*source_voice)
			return false;

		XAUDIO2_VOICE_STATE state;
		(*source_voice)->GetState(&state);
	
		if (state.BuffersQueued > 0)
			return true;
		else
			return false;
	}


//	개인함수:
private:
	void	initializeXAudio2()
	{
		CoInitializeEx( NULL, COINIT_MULTITHREADED );

		if( FAILED( XAudio2Create(&_xaudio2, DEFAULT_CAUDIO_INTIALIZE_XAUDIO_FLAG)) )
		{
			CError	e
			(
				_T("경고XX:\tXAudio2 초기화 실패. 소리가 나오지 않습니다."), 
				_T("해결방법"),
				_T(__FUNCTION__)
			);
			e.log();
			release();
		}		
	}
	void	release()
	{
		releaseResource();
		//releaseDevice();	//	일부 컴퓨터에서 에러가 발생한다. 그리고 에러가 발생하면 그 이후의 모든 작업이 캔슬되므로 (이유는 정말 모르겠음) 하는 수없이, 그냥 놔둔다
		//CoUninitialize();	
		_enable = false; // CAudio자체는 남아있음. 하지만 장치가 unload됨을 알리기 위해 enable을 false로 함
	}
	void	releaseDevice()
	{
		
		if (_fx_submix)
		{
			_fx_submix->DestroyVoice();
			_fx_submix = NULL;
		}
		if (_music_submix)
		{
			_music_submix->DestroyVoice();
			_music_submix = NULL;
		}		
		if (_mastering_voice)
		{
			_mastering_voice->DestroyVoice();			
			_mastering_voice = NULL;
		}		
		if (_xaudio2)
		{
			_xaudio2->Release();			
			_xaudio2 = NULL;
		}
	}
	void	releaseResource()
	{
		releaseMusicResource();
		releaseSoundResource();
		releaseMusicSource();
		releaseSoundSource();
	}
	void	releaseMusicSource()
	{		
		if (_music_source)
		{
			_music_source->DestroyVoice();
			_music_source = NULL;
		}
	}
	void	releaseSoundSource()
	{
		if (_fx_source)
		{
			for (int n=0; n < _fx_max_channel ;n++)
			{
				if ( _fx_source[n] )
				{
					_fx_source[n]->DestroyVoice();
					_fx_source[n] = NULL;
				}			
			}

			delete [] _fx_source;
			_fx_source = NULL;
		}
	}
	void	releaseMusicResource()
	{
		if (_music_file)
		{
			for (int n=0; n < _music_bank_size ;n++) // size는 index.
			{
				_music_file[n].release();
			}

			delete [] _music_file;
			_music_file = NULL;
		}
	}
	void	releaseSoundResource()
	{
		if (_fx_file)
		{
			for (int n=0; n < _fx_bank_size ;n++) // size는 index.
			{	
				_fx_file[n].release();
			}

			delete [] _fx_file;
			_fx_file = NULL;
		}
	}
	void	initializeMasteringVoice()
	{
		if( FAILED( _xaudio2->CreateMasteringVoice(&_mastering_voice)) )
		{
			CError	e
			(
				_T("경고XX:\t마스터링 보이스 초기화 실패. 소리가 나오지 않습니다."), 
				_T("해결방법"),
				_T(__FUNCTION__)
			);			
			e.log();

			release();
		}
	}
	void	initializeSubmixVoice()
	{
		if( FAILED(_xaudio2->CreateSubmixVoice(&_fx_submix, 2, 44100 ) ) )
		{
			CError	e
			(
				_T("경고XX:\t효과음 서브믹스 보이스 초기화 실패. 소리가 나오지 않습니다."), 
				_T("해결방법"),
				_T(__FUNCTION__)
			);	
			e.log();

			release();
		}
		if( FAILED( _xaudio2->CreateSubmixVoice(&_music_submix, 2, 44100 ) ) )
		{
			CError	e
			(
				_T("경고XX:\t음악 서브믹스 보이스 초기화 실패. 소리가 나오지 않습니다."), 
				_T("해결방법"),
				_T(__FUNCTION__)
			);	
			e.log();

			release();
		}
	}
	void	initializeMusicBuffer()
	{
		_music_buffer.AudioBytes = 0;
		_music_buffer.Flags = 0;
		_music_buffer.LoopBegin = 0;
		_music_buffer.LoopCount = 0;
		_music_buffer.LoopLength = 0;
		_music_buffer.pAudioData = 0;
		_music_buffer.pContext = 0;
		_music_buffer.PlayBegin = 0;
		_music_buffer.PlayLength = 0;
	}


	void	initializeSoundSource()
	{
		if (_fx_source)
			releaseSoundSource();

		_fx_source = new IXAudio2SourceVoice*[_fx_max_channel];
		for (int n=0; n < _fx_max_channel ;n++)
		{
			_fx_source[n] = NULL;
		}
	}
//	멤버변수:
public:
	IXAudio2SubmixVoice*	_fx_submix;
	IXAudio2SubmixVoice*	_music_submix;

//	개인변수:
private:
	//	xaudio:
	IXAudio2*				_xaudio2;
	IXAudio2MasteringVoice* _mastering_voice;	
	//	BANK:
	//		효과음:
	CAudioBuffer*	_fx_file; //_fx_file[_fx_bank_capacity]
	int				_fx_bank_size;
	int				_fx_bank_capacity;
	//		음악:
	CAudioBuffer*	_music_file;
	int				_music_bank_size;
	int				_music_bank_capacity;
	//	SOURCEVOICE:
	//		효과음:
	IXAudio2SourceVoice*	*_fx_source;
	int						_fx_max_channel; // ini에서 가져옴
	//		음악:
	IXAudio2SourceVoice*	_music_source; // 하나만 가능
	XAUDIO2_BUFFER			_music_buffer;

	//	상태변수
	bool	_enable;
};