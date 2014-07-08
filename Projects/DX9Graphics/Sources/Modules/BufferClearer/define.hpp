#ifdef _DEBUG
#	ifdef DEVELOPER
#		define	_NAME				"BufferClearer"
#		define	_DEVELOPER			"kniz"
#		define	_REVISION			1
#		define	_COMMENT			"0번: 모듈셀렉터로 바인딩하여, 버퍼를 비운다.\n1번: 비울 버퍼의 색\n2번. FLAG"
#		define	_VERSION			"0.0.1a"
#		define	_DATE				"2013-01-29"
#		define	_DEPENDENCIES_COUNT	0
#		define	_KEY_COUNT			2
#		define	_DEFAULT_COLOR		D3DCOLOR_ARGB(255, 0, 0, 75)
#		define	_DEFAULT_FLAG		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
#	endif
#else
#	ifdef DEVELOPER
#		define	_NAME				"BufferClearer"
#		define	_DEVELOPER			"kniz"
#		define	_REVISION			1
#		define	_COMMENT			"0번: 모듈셀렉터로 바인딩하여, 버퍼를 비운다.\n1번: 비울 버퍼의 색\n2번. FLAG"
#		define	_VERSION			"0.0.1a"
#		define	_DATE				"2013-01-29"
#		define	_DEPENDENCIES_COUNT	0
#		define	_KEY_COUNT			2
#		define	_DEFAULT_COLOR		D3DCOLOR_ARGB(255, 0, 0, 75)
#		define	_DEFAULT_FLAG		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
#	else
#		define	_NAME				"BufferClearer"
#		define	_DEVELOPER			"kniz"
#		define	_REVISION			1
#		define	_COMMENT			"0번: 모듈셀렉터로 바인딩하여, 버퍼를 비운다.\n1번: 비울 버퍼의 색\n2번. FLAG"
#		define	_VERSION			"0.0.1a"
#		define	_DATE				"2013-01-29"
#		define	_DEPENDENCIES_COUNT	0
#		define	_KEY_COUNT			2
#		define	_DEFAULT_COLOR		D3DCOLOR_ARGB(255, 0, 0, 75)
#		define	_DEFAULT_FLAG		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
#	endif
#endif