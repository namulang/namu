#ifdef _DEBUG
#	ifdef DEVELOPER
#		define	_NAME				"Model"
#		define	_DEVELOPER			"kniz"
#		define	_REVISION			1
#		define	_COMMENT			"\n0번: TranslationX \n1번: TranlationY \n2번: TranslationZ \n3번: RotationX \n4번: RotationY \n5번: RotationZ \n6번: ScalingX \n7번: ScalingY \n8번: ScalingZ \n9번: ColorRed \n10번. ColorGreen \n11번. ColorBlue \n12번. ColorAlpha \n13번: SourceBlending(0은 카메라의 값으로 자동적용) \n14번: DestBlending(0은 카메라 값으로 자동적용)\n15번: SubModels \n16번. 렌더링을 하는가? \n17번: Modeling모듈 \n18번: Texture모듈 \n19번. 텍스트를 넣을것인가? \n20번. 넣는다면, 텍스터 모듈"
#		define	_VERSION			"0.0.1a"
#		define	_DATE				"2013-08-08"
#		define	_DEPENDENCIES_COUNT	0
#		define	_KEY_COUNT			2
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