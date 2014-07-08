#include "CWaveLoader.hpp"
#include "CAudioBuffer.hpp"
//-----------------------------------------------------------------------------
// Name: CWaveLoader::CWaveLoader()
// Desc: Constructs the class.  Call Open() to open a wave file for reading.
//       Then call Read() as needed.  Calling the destructor or Close()
//       will close the file.
//-----------------------------------------------------------------------------
CWaveLoader::CWaveLoader()
{
	m_hmmio = NULL;
}


//-----------------------------------------------------------------------------
// Name: CWaveLoader::~CWaveLoader()
// Desc: Destructs the class
//-----------------------------------------------------------------------------
CWaveLoader::~CWaveLoader()
{
	close();
}


//-----------------------------------------------------------------------------
// Name: CWaveLoader::Open()
// Desc: Opens a wave file for reading
//-----------------------------------------------------------------------------
HRESULT CWaveLoader::open(CString strFileName, CAudioBuffer* audio_buffer)
{
	HRESULT hr;
	#ifdef UNICODE
		LPWSTR	filename = (LPWSTR)(LPCWSTR)strFileName;
	#else
		LPSTR	filename = (LPSTR)(LPCSTR)strFileName;
	#endif

	m_hmmio = mmioOpen(filename, NULL, MMIO_ALLOCBUF | MMIO_READ );

	if( FAILED( hr = readMMIO(audio_buffer) ) )
	{
		// ReadMMIO will fail if its an not a wave file
		mmioClose( m_hmmio, 0 );
		CError	e
		(
			_T("경고XX:\t readMMIO 실패. 파일명:" + strFileName), 
			_T("해결방법"),
			_T(__FUNCTION__)
		);
	}

	if( FAILED( hr = resetFile() ) )
	{
		CError	e
		(
			_T("경고XX:\t resetFile 실패. 파일명:" + strFileName), 
			_T("해결방법"),
			_T(__FUNCTION__)
		);
		return E_FAIL;
	}

	// After the reset, the size of the wav file is m_ck.cksize so store it now
	audio_buffer->_wave_size = m_ck.cksize;

	return hr;
}
//-----------------------------------------------------------------------------
// Name: CWaveLoader::ReadMMIO()
// Desc: Support function for reading from a multimedia I/O stream.
//       m_hmmio must be valid before calling.  This function uses it to
//       update m_ckRiff, and m_pwfx.
//-----------------------------------------------------------------------------
HRESULT CWaveLoader::readMMIO(CAudioBuffer* audio_buffer)
{
	MMCKINFO ckIn;           // chunk info. for general use.
	PCMWAVEFORMAT pcmWaveFormat;  // Temp PCM structure to load in.

	memset( &ckIn, 0, sizeof(ckIn) );

	if( ( 0 != mmioDescend( m_hmmio, &m_ckRiff, NULL, 0 ) ) )
		return E_FAIL;

	// Check to make sure this is a valid wave file
	if( ( m_ckRiff.ckid != FOURCC_RIFF ) ||
		( m_ckRiff.fccType != mmioFOURCC( 'W', 'A', 'V', 'E' ) ) )
		return E_FAIL;

	// Search the input file for for the 'fmt ' chunk.
	ckIn.ckid = mmioFOURCC( 'f', 'm', 't', ' ' );
	if( 0 != mmioDescend( m_hmmio, &ckIn, &m_ckRiff, MMIO_FINDCHUNK ) )
		return E_FAIL;

	// Expect the 'fmt' chunk to be at least as large as <PCMWAVEFORMAT>;
	// if there are extra parameters at the end, we'll ignore them
	if( ckIn.cksize < ( LONG )sizeof( PCMWAVEFORMAT ) )
		return E_FAIL;

	// Read the 'fmt ' chunk into <pcmWaveFormat>.
	if( mmioRead( m_hmmio, ( HPSTR )&pcmWaveFormat,
		sizeof( pcmWaveFormat ) ) != sizeof( pcmWaveFormat ) )
		return E_FAIL;

	// Allocate the waveformatex, but if its not pcm format, read the next
	// word, and thats how many extra bytes to allocate.
	if( pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM )
	{

		audio_buffer->_wave_format = ( WAVEFORMATEX* )new CHAR[ sizeof( WAVEFORMATEX ) ];
		if( NULL == audio_buffer->_wave_format )
			return E_FAIL;

		// Copy the bytes from the pcm structure to the waveformatex structure
		memcpy( audio_buffer->_wave_format, &pcmWaveFormat, sizeof( pcmWaveFormat ) );
		audio_buffer->_wave_format->cbSize = 0;
	}
	else
	{
		// Read in length of extra bytes.
		WORD cbExtraBytes = 0L;
		if( mmioRead( m_hmmio, ( CHAR* )&cbExtraBytes, sizeof( WORD ) ) != sizeof( WORD ) )
			return E_FAIL;

		audio_buffer->_wave_format = ( WAVEFORMATEX* )new CHAR[ sizeof( WAVEFORMATEX ) + cbExtraBytes ];
		if( NULL == audio_buffer->_wave_format )
			return E_FAIL;

		// Copy the bytes from the pcm structure to the waveformatex structure
		memcpy( audio_buffer->_wave_format, &pcmWaveFormat, sizeof( pcmWaveFormat ) );
		audio_buffer->_wave_format->cbSize = cbExtraBytes;

		// Now, read those extra bytes into the structure, if cbExtraAlloc != 0.
		if( mmioRead( m_hmmio, ( CHAR* )( ( ( BYTE* )&( audio_buffer->_wave_format->cbSize ) ) + sizeof( WORD ) ),
			cbExtraBytes ) != cbExtraBytes )
		{
			audio_buffer->releaseWaveFormat();
			audio_buffer->_wave_format = NULL;
			return E_FAIL;
		}
	}

	// Ascend the input file out of the 'fmt ' chunk.
	if( 0 != mmioAscend( m_hmmio, &ckIn, 0 ) )
	{
		audio_buffer->releaseWaveFormat();
		audio_buffer->_wave_format = NULL;
		return E_FAIL;
	}

	return S_OK;
}



//-----------------------------------------------------------------------------
// Name: CWaveLoader::ResetFile()
// Desc: Resets the internal m_ck pointer so reading starts from the
//       beginning of the file again
//-----------------------------------------------------------------------------
HRESULT CWaveLoader::resetFile()
{
	if( m_hmmio == NULL )
		return CO_E_NOTINITIALIZED;

	// Seek to the data
	if( -1 == mmioSeek( m_hmmio, m_ckRiff.dwDataOffset + sizeof( FOURCC ),
		SEEK_SET ) )
		return E_FAIL;

	// Search the input file for the 'data' chunk.
	m_ck.ckid = mmioFOURCC( 'd', 'a', 't', 'a' );
	if( 0 != mmioDescend( m_hmmio, &m_ck, &m_ckRiff, MMIO_FINDCHUNK ) )
		return E_FAIL;

	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: CWaveLoader::Read()
// Desc: Reads section of data from a wave file into pBuffer and returns
//       how much read in pdwSizeRead, reading not more than dwSizeToRead.
//       This uses m_ck to determine where to start reading from.  So
//       subsequent calls will be continue where the last left off unless
//       Reset() is called.
//-----------------------------------------------------------------------------
HRESULT CWaveLoader::read( CAudioBuffer* audio_buffer, DWORD dwSizeToRead )
{
	MMIOINFO mmioinfoIn; // current status of m_hmmio

	if( m_hmmio == NULL )
		return CO_E_NOTINITIALIZED;
	if( audio_buffer->_wave_data == NULL || audio_buffer->_wave_size == NULL )
		return E_INVALIDARG;

	audio_buffer->_wave_size = 0;

	if( 0 != mmioGetInfo( m_hmmio, &mmioinfoIn, 0 ) )
		return E_FAIL;

	UINT cbDataIn = dwSizeToRead;
	if( cbDataIn > m_ck.cksize )
		cbDataIn = m_ck.cksize;

	m_ck.cksize -= cbDataIn;

	for( DWORD cT = 0; cT < cbDataIn; cT++ )
	{
		// Copy the bytes from the io to the buffer.
		if( mmioinfoIn.pchNext == mmioinfoIn.pchEndRead )
		{
			if( 0 != mmioAdvance( m_hmmio, &mmioinfoIn, MMIO_READ ) )
				return E_FAIL;

			if( mmioinfoIn.pchNext == mmioinfoIn.pchEndRead )
				return E_FAIL;
		}

		// Actual copy.
		*( ( BYTE* )audio_buffer->_wave_data + cT ) = *( ( BYTE* )mmioinfoIn.pchNext );
		mmioinfoIn.pchNext++;
	}

	if( 0 != mmioSetInfo( m_hmmio, &mmioinfoIn, 0 ) )
		return E_FAIL;

	audio_buffer->_wave_size = cbDataIn;

	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: CWaveLoader::Close()
// Desc: Closes the wave file
//-----------------------------------------------------------------------------
HRESULT CWaveLoader::close()
{
	if ( m_hmmio != NULL )
	{
		mmioClose( m_hmmio, 0 );
		m_hmmio = NULL;
	}

	return S_OK;
}

HRESULT	CWaveLoader::load(CString filename, CAudioBuffer* audio_buffer)
{
	audio_buffer->releaseWaveFormat();
	audio_buffer->_load_success = true;

	if ( FAILED( open(filename, audio_buffer)) )
		return E_FAIL;

	audio_buffer->_wave_data = new BYTE[audio_buffer->_wave_size];
	
	if ( FAILED( read( audio_buffer, audio_buffer->_wave_size)) )
		return E_FAIL;

	return S_OK;
}