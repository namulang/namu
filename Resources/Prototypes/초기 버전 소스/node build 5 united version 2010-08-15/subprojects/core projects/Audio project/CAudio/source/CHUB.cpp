#include "CHUB.hpp"

//	생성자
CHUB::CHUB(HINSTANCE hInstance, LPTSTR lpCmdLine, int nCmdShow)
:_window(hInstance, nCmdShow, &_ini, &_audio), _audio(64)
//	생성자구문의 순서가 중요하다. ini(파일읽고)-> window(ini에 윈도우 크기정보
//	로 생성)-> engine(파일정보와 윈도우핸들로 초기화)
{
	timeBeginPeriod(DEFAULT_CHUB_TIMER_PERIOD);
}
//	소멸자
CHUB::~CHUB()
{
	timeEndPeriod(DEFAULT_CHUB_TIMER_PERIOD);
}
//	메세지를 핸들하는 함수로 이동한다.
void	CHUB::handleMessage() 
{ 
	// 리소스
	
	_audio.initializeMusicCapacity(2); // 0
	_audio.loadMusic(_T("..\\resource\\moteke.ogg"));
	_audio.loadMusic(_T("..\\resource\\moteke.ogg"));
	_audio.initializeSoundCapacity(1); // 0 ~ 1
	_audio.loadSound(_T("..\\resource\\heli.wav"));
	
	_window.HandleMessage(); 
}