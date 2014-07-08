#ifdef _DEBUG
#	ifdef DEVELOPER
#		define	_NAME					"Texture"
#		define	_DEVELOPER				"kniz"
#		define	_REVISION				1
#		define	_COMMENT				"0번: DX9모듈 \n1번: 경로 \n2번: ColorKeyRed \n3번. ColorKeyGreen\n4번. ColorKeyBlue\n5번. ColorKeyAlpha"
#		define	_VERSION				"0.0.1a"
#		define	_DATE					"2013-08-07"
#		define	_DEPENDENCIES_COUNT		0
#		define	_KEY_COUNT				2
#		define	_COLORKEY_RED_KEYNAME	"colorKeyRed"
#		define	_DEFAULT_COLORKEY_RED	0
#		define	_COLORKEY_GREEN_KEYNAME	"colorKeyGreen"
#		define	_DEFAULT_COLORKEY_GREEN	0
#		define	_COLORKEY_BLUE_KEYNAME	"colorKeyBlue"
#		define	_DEFAULT_COLORKEY_BLUE	0
#		define	_COLORKEY_ALPHA_KEYNAME	"colorKeyAlpha"
#		define	_DEFAULT_COLORKEY_ALPHA	255
#	endif
#else
#	ifdef DEVELOPER
#		define	_NAME					"Texture"
#		define	_DEVELOPER				"kniz"
#		define	_REVISION				1
#		define	_COMMENT				"0번: DX9모듈 \n1번: 경로 \n2번: ColorKeyRed \n3번. ColorKeyGreen\n4번. ColorKeyBlue\n5번. ColorKeyAlpha"
#		define	_VERSION				"0.0.1a"
#		define	_DATE					"2013-08-07"
#		define	_DEPENDENCIES_COUNT		0
#		define	_KEY_COUNT				2
#		define	_COLORKEY_RED_KEYNAME	"colorKeyRed"
#		define	_DEFAULT_COLORKEY_RED	0
#		define	_COLORKEY_GREEN_KEYNAME	"colorKeyGreen"
#		define	_DEFAULT_COLORKEY_GREEN	0
#		define	_COLORKEY_BLUE_KEYNAME	"colorKeyBlue"
#		define	_DEFAULT_COLORKEY_BLUE	0
#		define	_COLORKEY_ALPHA_KEYNAME	"colorKeyAlpha"
#		define	_DEFAULT_COLORKEY_ALPHA	255
#	else
#		define	_NAME					"Texture"
#		define	_DEVELOPER				"kniz"
#		define	_REVISION				1
#		define	_COMMENT				"0번: 모듈셀렉터로 바인딩하여, 버퍼를 비운다.\n1번: 비울 버퍼의 색\n2번. FLAG"
#		define	_VERSION				"0.0.1a"
#		define	_DATE					"2013-01-29"
#		define	_DEPENDENCIES_COUNT		0
#		define	_KEY_COUNT				2
#		define	_DEFAULT_COLOR			D3DCOLOR_ARGB(255, 0, 0, 75)
#		define	_DEFAULT_FLAG			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
#	endif
#endif