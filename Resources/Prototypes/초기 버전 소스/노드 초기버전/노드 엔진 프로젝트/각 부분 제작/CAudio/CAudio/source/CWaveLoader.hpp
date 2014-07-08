#pragma once

#include <xaudio2.h>
#include <Windows.h>
#include <tchar.h>
#include <atlstr.h> // CString을 API에서 사용하기위해

class CAudioBuffer;

class CWaveLoader
{
public:
	CWaveLoader();
	~CWaveLoader();

	HRESULT	load(CString filename, CAudioBuffer* audio_buffer);
	HRESULT open(CString strFileName, CAudioBuffer* audio_buffer );
	HRESULT close();

	HRESULT read( CAudioBuffer* audio_buffer, DWORD dwSizeToRead);

	HRESULT resetFile();
public:
	HMMIO m_hmmio;       // MM I/O handle for the WAVE
	MMCKINFO m_ck;          // Multimedia RIFF chunk
	MMCKINFO m_ckRiff;      // Use in opening a WAVE file	
	MMIOINFO m_mmioinfoOut;

protected:
	HRESULT readMMIO(CAudioBuffer* audio_buffer);	
};