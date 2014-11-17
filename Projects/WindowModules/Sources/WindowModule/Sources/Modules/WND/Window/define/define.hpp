#ifdef DEVELOPER
#	ifdef _DEBUG
#		define _NAME						"Window"
#		define _DEVELOPER					"haku"
#		define _REVISION					1 // 커널에서 판별하는 버전표기
#		define _VERSION						"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#		define _COMMENT						"윈도우를 생성한다.\n0: 윈도우의 X\n1: 윈도우의 Y\n2: 윈도우의 너비\n3: 윈도우의 높이\n4: 윈도우가 어떻게 보여질 것인가(5: 기본값\n5: 윈도우 제목"
#		define	_DATE						"2012-04-16"
#		define _DEPENDENCIES_COUNT			0
#		define _KEY_NUMBER					1

#		define _DEFAULT_WINDOW_STYLE		WS_OVERLAPPEDWINDOW | WS_VISIBLE
#		define _DEFAULT_WINDOW_TITLE		"Default Window"
#		define _DEFAULT_WINDOW_CLASS_NAME	"Window Class Of WindowModule"
#	else
#		define _NAME						"Window"
#		define _DEVELOPER					"haku"
#		define _REVISION					1 // 커널에서 판별하는 버전표기
#		define _VERSION						"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#		define _COMMENT						"윈도우를 생성한다.\n0: 윈도우의 X\n1: 윈도우의 Y\n2: 윈도우의 너비\n3: 윈도우의 높이\n4: 윈도우가 어떻게 보여질 것인가(5: 기본값\n5: 윈도우 제목"
#		define	_DATE						"2012-04-16"
#		define _DEPENDENCIES_COUNT			0
#		define _KEY_NUMBER					1

#		define _DEFAULT_WINDOW_STYLE		WS_OVERLAPPEDWINDOW | WS_VISIBLE
#		define _DEFAULT_WINDOW_TITLE		"Default Window"
#		define _DEFAULT_WINDOW_CLASS_NAME	"Window Class Of WindowModule"
#	endif
#else
#	define _NAME							"Window"
#	define _DEVELOPER						"haku"
#	define _REVISION						1 // 커널에서 판별하는 버전표기
#	define _VERSION							"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#		define _COMMENT						"윈도우를 생성한다.\n0: 윈도우의 X\n1: 윈도우의 Y\n2: 윈도우의 너비\n3: 윈도우의 높이\n4: 윈도우가 어떻게 보여질 것인가(5: 기본값\n5: 윈도우 제목"
#	define	_DATE							"2012-04-16"
#	define _DEPENDENCIES_COUNT				0
#	define _KEY_NUMBER						1

#	define _DEFAULT_WINDOW_STYLE			WS_OVERLAPPEDWINDOW | WS_VISIBLE
#	define _DEFAULT_WINDOW_TITLE			"Default Window"
#	define _DEFAULT_WINDOW_CLASS_NAME		"Window Class Of WindowModule"
#endif

