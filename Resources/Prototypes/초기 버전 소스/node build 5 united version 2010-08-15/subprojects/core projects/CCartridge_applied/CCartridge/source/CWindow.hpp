/*
	파일명:	CWindow.hpp
	이름:	윈도우 클래스
	기능:	윈도우의 형태를 관리한다	
*/
#pragma once
//	선언:
//		기본 인클루드:
#include <windows.h>
#include <tchar.h> // 유니코드 매크로 지원
//		커스텀 인클루드:
#include "CINI.hpp"
#include "define.hpp"
#include "CInput.hpp"
//		전방선언:

//		함수:
LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
//	정의:
//		클래스:
class CWindow
{
//	멤버함수:
public:	
	//	생성자:
	CWindow(HINSTANCE hInstance, int nCmdShow, CInput* input);
	//	소멸자:
	~CWindow();	
	//	일반함수:
	void	HandleMessage();

//	개인함수:	
private:
	//	초기화:
	void	initializeWindowClass();	
	void	initializeWindow();		
	//	일반함수:
	void	setClientRect();
	void	isAlreadyExcuted();



//	개인변수:
private:	
	//		일반:	
	MSG			_msg;	
	HINSTANCE	_hInstance;
	int			_nCmdShow;	
	//		접근자변수:
	CInput*		_input;
	HWND	_hWnd;
};
