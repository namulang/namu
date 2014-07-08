/*
	파일명:	CError.hpp
	이름:	에러 클래스
	기능:	오류정보(오류이름, 조치사항, 오류난 함수명, 시간, 날짜)를 error.log
			에 저장하고, 심각한 경우는 메세지박스를 띄워서 종료한다.
			(사실, 메세지박스띄우고 종료하는건, main.cpp에서 CHUB가 하고있음)
*/
#pragma once
//	선언:
//		기본 인클루드:
#include <fstream>
#include <time.h>
#include <atlstr.h>
#include <windows.h>
#include <tchar.h>
//		커스텀 인클루드:
#include "define.hpp"
//		전방선언:
class CWindow;
//		네임스페이스:
using namespace std;
//	정의:
//		클래스:
class CError
{
//	멤버 함수:
public:
	//	생성자:
	CError(CString error_name, CString error_explain, CString function_name, bool never_alert = false);
	//	소멸자:
	~CError();
	//	기록:	
	void	log(); 	
	void	showMessage();

//	개인 함수:
private:		
	//	시간 및 날짜:
	CString	getCurrentDate();
	CString	getCurrentTime();	


	
//	멤버 변수:
public:	
	//	에러정보:
	CString	_error_name,
			_error_explain,
			_function_name;	
	//	상태변수:
	bool	_never_alert; // 로그 기록하지 않음
};
