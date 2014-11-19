#define _NAME						"Window"
#define _DEVELOPER					"haku"
#define _REVISION					1 // 커널에서 판별하는 버전표기
#define _VERSION					"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#define _COMMENT					"처음 실행시 윈도우를 생성합니다.\n 2번째 부터는, 윈도우를 새로 업데이트 합니다."
#define	_DATE						"2012-04-16"
#define _DEPENDENCIES_COUNT			0
#define _KEY_NUMBER					6
#define _KEY_COMMENT_1				"왼쪽 좌표(X)"
#define _KEY_COMMENT_2				"위 좌표(Y)"
#define _KEY_COMMENT_3				"윈도우의 너비(Width)"
#define _KEY_COMMENT_4				"윈도우의 높이(Height)"
#define _KEY_COMMENT_5				"윈도우가 어떻게 보여질 것인가 (보통 : 5)"
#define _KEY_COMMENT_6				"윈도우의 제목"
#define _DEFAULT_WINDOW_STYLE		WS_OVERLAPPEDWINDOW | WS_VISIBLE
#define _DEFAULT_WINDOW_TITLE		"Default Window"
#define _DEFAULT_WINDOW_CLASS_NAME	"Window Class Of WindowModule"