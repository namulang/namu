/*
	파일명:	CHUB.hpp
	이름:	HUB; 허브
	기능:	모든 각 클래스를 연결하는 몸통	
*/
#pragma once
//	선언:
//		라이브러리:
#pragma comment (lib, "winmm.lib")
//		기본 인클루드:
#include <Windows.h>
#include <MMSystem.h>
#include <time.h>
//		커스텀 인클루드:
#include "CEngine.hpp"
#include "CWindow.hpp"
#include "CScripter.hpp"
#include "CINI.hpp"
#include "define.hpp"

//	정의:
//		클래스:
class CHUB
{
//	멤버 함수:
public:
	//	생성자:
	CHUB(HINSTANCE hInstance, LPTSTR lpCmdLine, int nCmdShow);	
	//	소멸자:
	~CHUB();	
	//	메세지:
	void	handleMessage();



//	멤버변수:
private:
	//	클래스접근자:
	CINI		_ini; // INI가 가장먼저 초기화 되야 한다.
	CWindow		_window; // 윈도우를 생성한다.
	CEngine		_engine; // CWindow 다음에 CEngine이 인스턴스 되야한다.	
	CScripter	_scripter;
};