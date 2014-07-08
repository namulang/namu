#ifdef _DEBUG
#	ifdef DEVELOPER
#		define	_NAME				"MosaicProgram.dev.dbg"
#		define	_DEVELOPER			"kniz"
#		define	_REVISION			1
#		define	_COMMENT			"0번: 모듈셀렉터로 바인딩하여, 버퍼를 비운다.\n1번: 렌더타겟의 Width비율(X방향Blur강도) \n2번: 렌더타겟의 Height비율(Y방향Blur강도) \n3번: 최종렌더될 타겟(0: 화면에 출력 1: 새로운 버퍼에 초기화 후 담기 2: 이전 버퍼에 덮어쓰기) \n4번: 모자이크 정밀도(기본 30)"
#		define	_VERSION			"0.0.1a"
#		define	_DATE				"2013-08-29"
#		define	_DEPENDENCIES_COUNT	0
#		define	_KEY_COUNT			1
#	endif
#else
#	ifdef DEVELOPER
#		define	_NAME				"Model.dev"
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
#		define	_NAME				"Model"
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