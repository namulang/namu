#include "XAudio2OGGDecoder.hpp"

#include <vorbis\codec.h>
#include <vorbis\vorbisfile.h>
#ifdef	_DEBUG
#	pragma comment(lib, "libogg.dbg.lib")
#	pragma comment(lib, "libvorbis.dbg.lib")
#else
#	pragma comment(lib, "libogg.lib")
#	pragma comment(lib, "libvorbis.lib")
#endif

namespace XA2
{
	type_result XAudio2OGGDecoder::_open(const NETString& strFileName)
	{
		FILE*	f;
		errno_t err;
#ifdef UNICODE
		err = _wfopen_s(&f, strFileName.toCharPointer(), _T("rb"));
#else
		err = fopen_s(&f, strFileName.toCharPointer(), _T("rb"));
#endif

		if (err != 0)
			return ALERT_ERROR("경고XX:\t Ogg, fopen 실패. 파일명:%s", strFileName.toCharPointer());


		OggVorbis_File vf;
#ifndef _WINDOWS
		// if(ov_open(f, &vf, NULL, 0) < 0)	//Windows does not like this function so we use ov_open_callbacks() instead
#else
		if (ov_open_callbacks(f, &vf, NULL, 0, OV_CALLBACKS_DEFAULT) < 0)
#endif
		{
			fclose(f);
			return ALERT_ERROR("경고XX:\t Ogg, ov_open 실패. 파일명:%s", strFileName.toCharPointer());
		}

		//The vorbis_info struct keeps the most of the interesting format info
		vorbis_info *vi = ov_info(&vf, -1);

		//Set the wave format

		//memset(_wave_format, 0, sizeof(WAVEFORMATEX));
		if (_wave_format)
		{
			delete _wave_format;
			_wave_format = NULL;
		}
		_wave_format = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
		memset(_wave_format, 0, sizeof(WAVEFORMATEX));
		_wave_format->cbSize = sizeof(WAVEFORMATEX);
		_wave_format->nChannels = vi->channels;
		_wave_format->wBitsPerSample = 16;                    //Ogg vorbis is always 16 bit
		_wave_format->nSamplesPerSec = vi->rate;
		_wave_format->nAvgBytesPerSec = _wave_format->nSamplesPerSec * _wave_format->nChannels * 2;
		_wave_format->nBlockAlign = 2 * _wave_format->nChannels;
		_wave_format->wFormatTag = 1;


		//	채널*샘플비트*PCM/8bits , 또는 채널*샘플비트*샘플레이트*시간/8bits 의 식을
		//	이용하여 총 바이트수를 계산하며 시간의 경우 ov_time_total()을 이용하여 구한다.
		type_uint wave_size = vi->channels * 16 * (DWORD)(ov_pcm_total(&vf, -1) / 8);
		arg_raw_pcm_size.setValue(wave_size);
		CHAR*	data = new CHAR[wave_size];

		//	read:	
		DWORD	pos = 0;
		int		ret = 1;
		int		bitstream = 0;
		while (ret && pos <= wave_size)
		{
			ret = ov_read(&vf, data + pos, wave_size - pos, 0, 2, 1, &bitstream);
			pos += ret;
		}

		_wave_data = (BYTE*)data;
		//	close:
		ov_clear(&vf);
		fclose(f);


		return S_OK;
	}
}