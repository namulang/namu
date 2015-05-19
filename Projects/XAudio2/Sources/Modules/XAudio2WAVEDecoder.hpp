#pragma once

#include "XAudio2Decoder.hpp"
#pragma comment(lib, "winmm.lib")

namespace XA2
{
	class NE_DLL XAudio2WAVEDecoder : public XAudio2Decoder
	{
	public:
		typedef XAudio2WAVEDecoder ThisClass;
		typedef XAudio2Decoder SuperClass;

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader instance;

			if (NEResult::hasError(instance.isValid()))
			{
				instance.getName() = "XAudio2WAVEDecoder";
				instance.getDeveloper() = "kniz";
				instance.setRevision(1);
				instance.getVersion() = "0.0.1a";
				instance.getReleaseDate() = "2015-05-07";
				instance.getComment() = 
					".wav 파일을 읽는 Module 입니다.\n"
					"XAudio2Player에 사용됩니다.";
				instance.getArgumentsComments() = SuperClass::getHeader().getArgumentsComments();
			}

			return instance;
		}
		virtual const NETString& getFileExtension() const
		{
			static NETString str(".wav");

			return str;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	protected:
		virtual type_result _onDecode(const NETString& path)
		{
			_release();

			if (FAILED(_open(path)))
				return ALERT_ERROR(" : open 실패");

			_wave_data = new type_ubyte[arg_raw_pcm_size.getValue()];

			if(FAILED(_read(arg_raw_pcm_size.getValue())))
				return ALERT_ERROR(" : Read 실패");


			arg_load_success.setValue(true);
			return RESULT_SUCCESS;
		}

	private:
		HRESULT _readMMIO()
		{
			MMCKINFO ckIn;           // chunk info. for general use.
			PCMWAVEFORMAT pcmWaveFormat;  // Temp PCM structure to load in.

			memset(&ckIn, 0, sizeof(ckIn));

			if ((0 != mmioDescend(m_hmmio, &m_ckRiff, NULL, 0)))
				return E_FAIL;

			// Check to make sure this is a valid wave file
			if ((m_ckRiff.ckid != FOURCC_RIFF) ||
				(m_ckRiff.fccType != mmioFOURCC('W', 'A', 'V', 'E')))
				return E_FAIL;

			// Search the input file for for the 'fmt ' chunk.
			ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
			if (0 != mmioDescend(m_hmmio, &ckIn, &m_ckRiff, MMIO_FINDCHUNK))
				return E_FAIL;

			// Expect the 'fmt' chunk to be at least as large as <PCMWAVEFORMAT>;
			// if there are extra parameters at the end, we'll ignore them
			if (ckIn.cksize < (LONG)sizeof(PCMWAVEFORMAT))
				return E_FAIL;

			// Read the 'fmt ' chunk into <pcmWaveFormat>.
			if (mmioRead(m_hmmio, (HPSTR)&pcmWaveFormat,
				sizeof(pcmWaveFormat)) != sizeof(pcmWaveFormat))
				return E_FAIL;

			// Allocate the waveformatex, but if its not pcm format, read the next
			// word, and thats how many extra bytes to allocate.
			if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
			{

				_wave_format = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
				if ( ! _wave_format)
					return E_FAIL;

				// Copy the bytes from the pcm structure to the waveformatex structure
				memcpy(_wave_format, &pcmWaveFormat, sizeof(pcmWaveFormat));
				_wave_format->cbSize = 0;
			}
			else
			{
				// Read in length of extra bytes.
				WORD cbExtraBytes = 0L;
				if (mmioRead(m_hmmio, (CHAR*)&cbExtraBytes, sizeof(WORD)) != sizeof(WORD))
					return E_FAIL;

				_wave_format = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX) + cbExtraBytes];
				if( ! _wave_format)
					return E_FAIL;

				// Copy the bytes from the pcm structure to the waveformatex structure
				memcpy(_wave_format, &pcmWaveFormat, sizeof(pcmWaveFormat));
				_wave_format->cbSize = cbExtraBytes;

				// Now, read those extra bytes into the structure, if cbExtraAlloc != 0.
				if (mmioRead(m_hmmio, (CHAR*)(((BYTE*)&(_wave_format->cbSize)) + sizeof(WORD)),
					cbExtraBytes) != cbExtraBytes)
				{
					_release();
					_wave_format = NULL;
					return E_FAIL;
				}
			}

			// Ascend the input file out of the 'fmt ' chunk.
			if (0 != mmioAscend(m_hmmio, &ckIn, 0))
			{
				_release();
				_wave_format = NULL;
				return E_FAIL;
			}

			return S_OK;
		}

		HRESULT _resetFile()
		{
			if (m_hmmio == NULL)
				return CO_E_NOTINITIALIZED;

			// Seek to the data
			if (-1 == mmioSeek(m_hmmio, m_ckRiff.dwDataOffset + sizeof(FOURCC),
				SEEK_SET))
				return E_FAIL;

			// Search the input file for the 'data' chunk.
			m_ck.ckid = mmioFOURCC('d', 'a', 't', 'a');
			if (0 != mmioDescend(m_hmmio, &m_ck, &m_ckRiff, MMIO_FINDCHUNK))
				return E_FAIL;

			return S_OK;
		}

		HRESULT _open(const NETString& strFileName)
		{
			HRESULT hr;

			m_hmmio = mmioOpen((LPWSTR) strFileName.toCharPointer(), NULL, MMIO_ALLOCBUF | MMIO_READ);

			if (FAILED(hr = _readMMIO()))
			{
				// ReadMMIO will fail if its an not a wave file
				mmioClose(m_hmmio, 0);
				return ALERT_ERROR("경고XX:\t readMMIO 실패. 파일명: %s", strFileName.toCharPointer());
			}

			if(FAILED(hr = _resetFile()))
				return ALERT_ERROR("경고XX:\t resetFile 실패. 파일명: %s", strFileName.toCharPointer());

			// After the reset, the size of the wav file is m_ck.cksize so store it now
			arg_raw_pcm_size.setValue(m_ck.cksize);

			return hr;
		}

		HRESULT _read(DWORD dwSizeToRead)
		{
			MMIOINFO mmioinfoIn; // current status of m_hmmio

			if (m_hmmio == NULL)
				return CO_E_NOTINITIALIZED;
			if( ! _wave_data || arg_raw_pcm_size.getValue() == 0)
				return E_INVALIDARG;

			arg_raw_pcm_size.setValue(0);

			if (0 != mmioGetInfo(m_hmmio, &mmioinfoIn, 0))
				return E_FAIL;

			UINT cbDataIn = dwSizeToRead;
			if (cbDataIn > m_ck.cksize)
				cbDataIn = m_ck.cksize;

			m_ck.cksize -= cbDataIn;

			for (DWORD cT = 0; cT < cbDataIn; cT++)
			{
				// Copy the bytes from the io to the buffer.
				if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
				{
					if (0 != mmioAdvance(m_hmmio, &mmioinfoIn, MMIO_READ))
						return E_FAIL;

					if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
						return E_FAIL;
				}

				// Actual copy.
				*((type_ubyte*)_wave_data + cT) = *((type_ubyte*)mmioinfoIn.pchNext);
				mmioinfoIn.pchNext++;
			}

			if (0 != mmioSetInfo(m_hmmio, &mmioinfoIn, 0))
				return E_FAIL;

			arg_raw_pcm_size.setValue(cbDataIn);

			return S_OK;
		}

	private:
		HMMIO m_hmmio;       // MM I/O handle for the WAVE
		MMCKINFO m_ck;          // Multimedia RIFF chunk
		MMCKINFO m_ckRiff;      // Use in opening a WAVE file	
		MMIOINFO m_mmioinfoOut;
	};
}