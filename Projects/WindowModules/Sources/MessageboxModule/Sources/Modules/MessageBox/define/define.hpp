#ifdef DEVELOPER
#	ifdef _DEBUG
#		define _NAME					"MessageBox"
#		define _DEVELOPER				"haku"
#		define _REVISION				1 // 커널에서 판별하는 버전표기
#		define _VERSION					"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#		define _COMMENT					"Windows 메시지 박스를 띄웁니다.\n0: 타이틀\n1: 내용"
#		define	_DATE					"2012-05-05"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				2
#		define _DEFAULT_MESSAGE			"hello world!"
#	else
#		define _NAME					"MessageBox"
#		define _DEVELOPER				"haku"
#		define _REVISION				1 // 커널에서 판별하는 버전표기
#		define _VERSION					"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#		define _COMMENT					"Windows 메시지 박스를 띄웁니다.\n0: 타이틀\n1: 내용"
#		define	_DATE					"2012-05-05"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				2
#		define _DEFAULT_MESSAGE			"hello world!"
#	endif
#else
#	define _NAME						"MessageBox"
#	define _DEVELOPER					"haku"
#	define _REVISION					1 // 커널에서 판별하는 버전표기
#	define _VERSION						"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#	define _COMMENT						"Windows 메시지 박스를 띄웁니다.\n0: 타이틀\n1: 내용"
#	define	_DATE						"2012-05-05"
#	define _DEPENDENCIES_COUNT			0
#	define _KEY_NUMBER					2
#	define _DEFAULT_MESSAGE				"hello world!"
#endif