/*
	파일명:	define.hpp
	이름:	NODE의 디폴트
	기능:	엔진 NODE에서 사용되는 모든 디폴트값이 들어있다. 어디 부분에서나 자유롭게 include해서 사용하면 된다.
*/
#pragma once
//	선언:
//		기본 인클루드:
#include <d3dx9.h>
//			CHUB:
#define DEFAULT_CHUB_TIMER_PERIOD							1
//			CWindow:
#define DEFAULT_CWINDOW_WINDOW_X							100
#define DEFAULT_CWINDOW_WINDOW_Y							100
#define DEFAULT_CWINDOW_WINDOW_NAME							_T("DirectX 9 Tutorial 2 - Triangle")
#define DEFAULT_CWINDOW_WINDOW_CLASSNAME					_T("DX9_TUTORIAL2_CLASS")
//			CINI:
//#define DEFAULT_CINI_AUDIO_WIDTH							640
//			CError:
#define	DEFAULT_CERROR_MESSAGEBOX_COMMENT_TOP				_T("다음과 같은 오류가 발생해, error.log에 기록 했습니다.\n\n")
#define DEFAULT_CERROR_MESSAGEBOX_COMMENT_BOTTOM			_T("\n\n해결방법을 모를경우엔, 홈페이지에 물어보십시오.")
//			화면비율:
typedef enum enum_window_ratio
{
	RATIO_4_3	= 0, // 1200x900
	RATIO_16_9	= 1, // 1600x900
	RATIO_16_10	= 2 // 1440x900
} WINDOW_RATIO;
typedef	enum enum_file_extention // #파일지원#추가#
{
	WAV,
	OGG,
	NOT_SUPPORT_EXTENTION
} FILE_EXTENTION;
