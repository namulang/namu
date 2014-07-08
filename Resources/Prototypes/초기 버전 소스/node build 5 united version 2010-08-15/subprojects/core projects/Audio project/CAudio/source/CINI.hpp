/*
	파일명:	CINI.hpp
	이름:	INI 로더
	기능:	시스템 설정(그래픽, 사운드, 버전) && 게임옵션 을 관리
*/

#pragma once
//	선언:
//		기본 인클루드:
#include <Windows.h>
#include <tchar.h>
#include <atlstr.h> // CString을 API에서 사용하기위해
//		커스텀 인클루드:
#include "CError.hpp"
#include "define.hpp"
//	정의:
//		클래스:
class CINI
{
//	멤버 함수:
public:
	//	생성자:
	CINI() 
	{}
	//	소멸자:
	~CINI()
	{

	}



//	개인변수:
private:
	//		화면 비율:
	WINDOW_RATIO	_graphic_ratio;
};