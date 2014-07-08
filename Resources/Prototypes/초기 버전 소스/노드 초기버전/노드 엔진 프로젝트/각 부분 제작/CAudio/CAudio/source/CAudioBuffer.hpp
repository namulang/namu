#pragma once

#include <xaudio2.h>
#include <Windows.h>
#include <tchar.h>
#include <atlstr.h> // CString을 API에서 사용하기위해
#include "define.hpp"
#include "CWaveLoader.hpp" // #파일지원#추가#
#include "COggLoader.hpp"
#include "CError.hpp"

class CAudioBuffer
{
public:
	CAudioBuffer(): _wave_format(NULL), _wave_size(0), _wave_data(NULL),
	_filename(_T("")), _load_success(false)
	{

	}
	~CAudioBuffer()
	{
		release();
	}
	void	release()
	{
		if (_load_success)
		{
			releaseWaveFormat();
			releaseWaveData();
			_load_success = false;
		}
	}
	void	releaseWaveFormat()
	{
		if (_wave_format)
		{
			delete [] _wave_format;
			_wave_format = NULL;
		}		
	}
	void	releaseWaveData()
	{
		if (_wave_data)
		{
			delete [] _wave_data;
			_wave_data = NULL;
		}		
	}
	void	load(CString filename)
	{
		//	메인코드: #파일지원#추가#
		switch(parseFilnameExtention(filename))
		{
		case WAV:
			{
				CWaveLoader wave_loader;
				if ( FAILED(wave_loader.load(filename, this)) )
				{
					CError	e
					(
						_T("경고XX:\t지원하는 음악파일이지만, 읽는데 실패했습니다. 파일이 재생되지 않습니다. 파일명: " + filename), 
						_T("해결방법"),
						_T(__FUNCTION__)
					);
					e.log();
					_load_success = false;
				}					
			}
			break;
		case OGG:
			{
				COggLoader ogg_loader;
				if ( FAILED(ogg_loader.load(filename, this)) )
				{
					CError	e
					(
						_T("경고XX:\t지원하는 음악파일이지만, 읽는데 실패했습니다. 파일이 재생되지 않습니다. 파일명: " + filename), 
						_T("해결방법"),
						_T(__FUNCTION__)
					);
					e.log();
					_load_success = false;
				}					
			}
			break;
		default:
			CError	e
			(
				_T("경고XX:\t지원하지않는 오디오 파일 확장자입니다. 파일을 읽지 않습니다. 파일명: " + filename), 
				_T("해결방법"),
				_T(__FUNCTION__)
			);
			e.log();
			_load_success = false;
		}
	}
	FILE_EXTENTION	parseFilnameExtention(CString filename)
	{		
		CString filename_extention = filename.Right(4);

		if ( filename_extention.CompareNoCase(_T(".wav")) == 0 )
		{
			return WAV;
		}
		else if ( filename_extention.CompareNoCase(_T(".ogg")) == 0 )
		{
			return OGG;
		}
		else 
			return NOT_SUPPORT_EXTENTION;
	}
	
public:
	bool			_load_success;
	WAVEFORMATEX*	_wave_format;
	DWORD			_wave_size;
	BYTE*			_wave_data; // 동적 배열
	CString			_filename;
	//	상태변수

};