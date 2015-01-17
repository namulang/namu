#		define	_NAME									"DX9"
#		define	_DEVELOPER								"kniz"
#		define	_REVISION								1
#		define	_COMMENT								"Microsoft의 DirectX9 Device를 초기화 합니다.\n" \
														"DX9Graphics 패키지의 다른 Module을 실행하기 위해서는 이 Module이 NodeManager 영역에 놓아져야 합니다.\n" \
														"Arguments들은 처음 실행시(초기화)에서만 사용되며, 이미 한번 초기화되면, 도중에 값이 변경되어도 적용되지 않습니다."
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