#define _NAME							"WNDDomainManipulator.dev.dbg"
#define _DEVELOPER						"kniz"
#define _REVISION						1 // 커널에서 판별하는 버전표기
#define _VERSION						"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#define _COMMENT						"0번셀렉터로 추출되는 모든 WND모듈의 크기를(2번키:x, 3번키:y, 4번키:width, 5번키:height)로 적용합니다.\n1번키로는 윈도우를 이동하고 나서 앞에다 놓을지 뒤에다 놓을지 정할수 있습니다.\n6번키로는 움직이고 난후의 윈도우의 상태를 결정할 수 있습니다."
#define	_DATE							"2012-05-03"
#define _DEPENDENCIES_COUNT				0
#define _KEY_NUMBER						7
#define _KEY_COMMENT_1					"변경할 Window 모듈"
#define _KEY_COMMENT_2					"이동할 왼쪽 좌표(X)"
#define _KEY_COMMENT_3					"이동할 위 좌표(Y)"
#define _KEY_COMMENT_4					"바뀌어질 윈도우의 너비(Width)"
#define _KEY_COMMENT_5					"바뀌어질 윈도우의 높이(Height)"
#define _KEY_COMMENT_6					"윈도우가 어떻게 보이게 할것인가 (보통 : 5)"
#define _KEY_COMMENT_7					"얼마나 윈도우를 상위로 할것인가를 결정한다. 상위로 가면 다른 윈도우를 덮으며 그려진다.\n0:상위로 1: 밑으로 -1: 맨 위로 -2: 맨 아래로"