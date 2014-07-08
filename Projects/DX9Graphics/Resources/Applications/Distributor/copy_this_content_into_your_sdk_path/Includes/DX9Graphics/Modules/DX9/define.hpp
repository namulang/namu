#ifdef _DEBUG
#	ifdef DEVELOPER
#		define	_NAME									"DX9.dev.dbg"
#		define	_DEVELOPER								"kniz"
#		define	_REVISION								1
#		define	_COMMENT								"1번: ini 사용하는가\n2번: 수직동기화 사용\n3번:윈도우 모드인가\n4번. 32비트모드\n5번. 32비트 텍스쳐 사용\n6번. 스크린 너비\n7번. 스크린 높이\n8번. 스크린 비율(너비/높이)\n9번. 백 버퍼 카운트\n10번. 스크린 갱신율(refresh rate)\n10번. SWAP방법(SWAP_EFFECT)\n11번. 칼라키\n12번. 기본배경색"
#		define	_VERSION								"0.0.1a"
#		define	_DATE									"2013-01-29"
#		define	_DEPENDENCIES_COUNT						0
#		define	_KEY_COUNT								12
//	keynames:
#		define	_KEYNAME_OF_IS_VERTICAL_SYNCHRONIZED	"isVerticalSynchronized"
#		define	_KEYNAME_OF_IS_WINDOW_MODE				"isWindowMode"
#		define	_KEYNAME_OF_IS_32BIT_COLOR_MODE			"is32bitColorMode"
#		define	_KEYNAME_OF_IS_32BIT_TEXTURE_MODE		"is32bitTextureMode"
#		define	_KEYNAME_OF_SCREEN_WIDTH				"screenWidth"
#		define	_KEYNAME_OF_SCREEN_HEIGHT				"screenHeight"
#		define	_KEYNAME_OF_SCREEN_RATIO				"screenRatio"
#		define  _KEYNAME_OF_BACK_BUFFER_COUNT			"backBufferCount"
#		define  _KEYNAME_OF_SCREEN_REFRESH_RATE			"screenRefreshRate"
#		define  _KEYNAME_OF_SWAP_EFFECT					"swapEffect"
#		define  _KEYNAME_OF_BACKGROUND_COLOR_KEY		"backgroundColor"
//	defaults:
#		define	_DEFAULT_IS_LOAD_FROM_INI_WHEN_START	true
#		define	_DEFAULT_IS_WINDOW_MODE					false			
#		define	_DEFAULT_IS_VERTICAL_SYNCHRONIZED		true
#		define	_DEFAULT_IS_32BIT_COLOR_MODE			true
#		define	_DEFAULT_IS_32BIT_TEXTURE_MODE			true
#		define	_DEFAULT_SCREEN_WIDTH					640
#		define	_DEFAULT_SCREEN_HEIGHT					480
#		define	_DEFAULT_SCREEN_RATIO					4.0f / 3.0f
#		define	_DEFAULT_BACK_BUFFER_COUNT				1
#		define	_DEFAULT_SCREEN_REFRESH_RATE			60
#		define	_DEFAULT_SWAP_EFFECT					D3DSWAPEFFECT_DISCARD
#		define	_DEFAULT_COLOR_KEY						255
#		define	_DEFAULT_BACKGROUND_COLOR_KEY			D3DCOLOR_ARGB(0, 0, 0, 0)
#	endif
#else
#	ifdef DEVELOPER
#		define	_NAME									"DX9.dev"
#		define	_DEVELOPER								"kniz"
#		define	_REVISION								1
#		define	_COMMENT								"0번: ini 사용하는가\n1번:윈도우 모드인가\n2번: 수직동기화 사용\n3번. 32비트모드\n4번. 32비트 텍스쳐 사용\n5번. 스크린 너비\n6번. 스크린 높이\n7번. 스크린 비율(너비/높이)\n8번. 백 버퍼 카운트\n9번. 스크린 갱신율(refresh rate)\n10번. SWAP방법(SWAP_EFFECT)\n11번. 칼라키\n12번. 기본배경색"
#		define	_VERSION								"0.0.1a"
#		define	_DATE									"2013-01-29"
#		define	_DEPENDENCIES_COUNT						0
#		define	_KEY_COUNT								14
//	keynames:
#		define	_KEYNAME_OF_VERTICAL_SYNCHRONIZED		"isVerticalSynchronized"
#		define	_KEYNAME_OF_IS_WINDOWED					"isWindowed"
#		define	_KEYNAME_OF_IS_32BIT_COLOR				"is32bitColor"
#		define	_KEYNAME_OF_IS_32BIT_TEXTURE			"is32bitTexture"
#		define	_KEYNAME_OF_SCREEN_WIDTH				"screenWidth"
#		define	_KEYNAME_OF_SCREEN_HEIGHT				"screenHeight"
#		define	_KEYNAME_OF_SCREEN_RATIO				"screenRatio"
#		define  _KEYNAME_OF_BACKBUFFER_COUNT			"backBufferCount"
#		define  _KEYNAME_OF_SCREEN_REFRESH_RATE			"screenRefreshRate"
#		define  _KEYNAME_OF_SWAP_EFFECT					"swapEffect"
#		define  _KEYNAME_OF_COLOR_KEY_ALPHA				"colorKeyAlpha"
#		define  _KEYNAME_OF_COLOR_KEY_RED				"colorKeyRed"
#		define  _KEYNAME_OF_COLOR_KEY_GREEN				"colorKeyGreen"
#		define  _KEYNAME_OF_COLOR_KEY_BLUE				"colorKeyBlue"
#		define  _KEYNAME_OF_BACKGROUND_COLOR_ALPHA		"backgroundColorAlpha"
#		define  _KEYNAME_OF_BACKGROUND_COLOR_RED		"backgroundColorRed"
#		define  _KEYNAME_OF_BACKGROUND_COLOR_GREEN		"backgroundColorGreen"
#		define  _KEYNAME_OF_BACKGROUND_COLOR_BLUE		"backgroundColorBlue"
#		define  _KEYNAME_OF_TEXTURE_PATHS				"texturePaths"
//	defaults:
#		define	_DEFAULT_IS_LOAD_FROM_INI_WHEN_START	true
#		define	_DEFAULT_IS_WINDOW_MODE					false			
#		define	_DEFAULT_IS_VERTICAL_SYNCHRONIZED		true
#		define	_DEFAULT_IS_32BIT_COLOR_MODE			true
#		define	_DEFAULT_IS_TEXTURE_32BIT				true
#		define	_DEFAULT_SCREEN_WIDTH					640
#		define	_DEFAULT_SCREEN_HEIGHT					480
#		define	_DEFAULT_SCREEN_RATIO					4.0f / 3.0f
#		define	_DEFAULT_BACK_BUFFER_COUNT				1
#		define	_DEFAULT_SCREEN_REFRESH_RATE			60
#		define	_DEFAULT_SWAP_EFFECT					D3DSWAPEFFECT_DISCARD
#		define	_DEFAULT_COLOR_KEY						D3DCOLOR_ARGB(255, 0, 0, 0)
#		define	_DEFAULT_BACKGROUND_COLOR_KEY			D3DCOLOR_ARGB(0, 0, 0, 0)
#	else
#		define	_NAME									"DX9"
#		define	_DEVELOPER								"kniz"
#		define	_REVISION								1
#		define	_COMMENT								"0번: ini 사용하는가\n1번:윈도우 모드인가\n2번: 수직동기화 사용\n3번. 32비트모드\n4번. 32비트 텍스쳐 사용\n5번. 스크린 너비\n6번. 스크린 높이\n7번. 스크린 비율(너비/높이)\n8번. 백 버퍼 카운트\n9번. 스크린 갱신율(refresh rate)\n10번. SWAP방법(SWAP_EFFECT)\n11번. 칼라키\n12번. 기본배경색"
#		define	_VERSION								"0.0.1a"
#		define	_DATE									"2013-01-29"
#		define	_DEPENDENCIES_COUNT						0
#		define	_KEY_COUNT								14
//	keynames:
#		define	_KEYNAME_OF_VERTICAL_SYNCHRONIZED		"isVerticalSynchronized"
#		define	_KEYNAME_OF_IS_WINDOWED					"isWindowed"
#		define	_KEYNAME_OF_IS_32BIT_COLOR				"is32bitColor"
#		define	_KEYNAME_OF_IS_32BIT_TEXTURE			"is32bitTexture"
#		define	_KEYNAME_OF_SCREEN_WIDTH				"screenWidth"
#		define	_KEYNAME_OF_SCREEN_HEIGHT				"screenHeight"
#		define	_KEYNAME_OF_SCREEN_RATIO				"screenRatio"
#		define  _KEYNAME_OF_BACKBUFFER_COUNT			"backBufferCount"
#		define  _KEYNAME_OF_SCREEN_REFRESH_RATE			"screenRefreshRate"
#		define  _KEYNAME_OF_SWAP_EFFECT					"swapEffect"
#		define  _KEYNAME_OF_COLOR_KEY_ALPHA				"colorKeyAlpha"
#		define  _KEYNAME_OF_COLOR_KEY_RED				"colorKeyRed"
#		define  _KEYNAME_OF_COLOR_KEY_GREEN				"colorKeyGreen"
#		define  _KEYNAME_OF_COLOR_KEY_BLUE				"colorKeyBlue"
#		define  _KEYNAME_OF_BACKGROUND_COLOR_ALPHA		"backgroundColorAlpha"
#		define  _KEYNAME_OF_BACKGROUND_COLOR_RED		"backgroundColorRed"
#		define  _KEYNAME_OF_BACKGROUND_COLOR_GREEN		"backgroundColorGreen"
#		define  _KEYNAME_OF_BACKGROUND_COLOR_BLUE		"backgroundColorBlue"
#		define  _KEYNAME_OF_TEXTURE_PATHS				"texturePaths"
//	defaults:
#		define	_DEFAULT_IS_LOAD_FROM_INI_WHEN_START	true
#		define	_DEFAULT_IS_WINDOW_MODE					false			
#		define	_DEFAULT_IS_VERTICAL_SYNCHRONIZED		true
#		define	_DEFAULT_IS_32BIT_COLOR_MODE			true
#		define	_DEFAULT_IS_TEXTURE_32BIT				true
#		define	_DEFAULT_SCREEN_WIDTH					640
#		define	_DEFAULT_SCREEN_HEIGHT					480
#		define	_DEFAULT_SCREEN_RATIO					4.0f / 3.0f
#		define	_DEFAULT_BACK_BUFFER_COUNT				1
#		define	_DEFAULT_SCREEN_REFRESH_RATE			60
#		define	_DEFAULT_SWAP_EFFECT					D3DSWAPEFFECT_DISCARD
#		define	_DEFAULT_COLOR_KEY						D3DCOLOR_ARGB(255, 0, 0, 0)
#		define	_DEFAULT_BACKGROUND_COLOR_KEY			D3DCOLOR_ARGB(0, 0, 0, 0)
#	endif
#endif