#pragma once

#ifdef	_DEBUG
#pragma comment(lib, "libogg_d.lib")
#pragma comment(lib, "libvorbis_d.lib")
#pragma comment(lib, "libvorbisfile_d.lib")
#else
#pragma comment(lib, "libogg.lib")
#pragma comment(lib, "libvorbis.lib")
#pragma comment(lib, "libvorbisfile.lib")
#endif

#include <xaudio2.h>
#include <Windows.h>
#include <tchar.h>
#include <atlstr.h> // CString을 API에서 사용하기위해

#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#define STREAMING_BUFFER_SIZE 65536*10 // 한번에 OGG -> WAV할 크기



//	OGG version		1. 2. 0
//	Vorbis version	1. 3. 1

class CAudioBuffer;

class COggLoader
{
public:
	COggLoader();
	~COggLoader();

	HRESULT	load(CString filename, CAudioBuffer* audio_buffer);
	HRESULT open(CString strFileName, CAudioBuffer* audio_buffer );

private:
	OggVorbis_File vf;
};