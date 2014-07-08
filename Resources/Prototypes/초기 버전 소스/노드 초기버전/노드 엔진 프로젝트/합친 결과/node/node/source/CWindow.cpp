#include "CWindow.hpp"
#include "CScripter.hpp"
#include "CError.hpp"

//	CHUB가 생성도중에 CError 메세지를 캐치해야하는데... CError는 윈도우 핸들을 CHUB로부터 얻는지라,
//	아직 생성되지않은 CHUB로부터 윈도우핸들을 얻을 수 없다 (윈도우 핸들은 메모리에 존재하지만..)
//	그래서 어쩔수없이 윈도우 핸들을 전역변수(스태틱)로 한다.
HWND	CWindow::_hWnd = 0;

CWindow::CWindow(HINSTANCE hInstance, int nCmdShow, CScripter* scripter, CINI* ini) 
: _hInstance(hInstance), _nCmdShow(nCmdShow), _scripter(scripter), _ini(ini)
{	
	//	초기화:
	isAlreadyExcuted();
	initializeWindowClass();
	initializeWindow();
	setClientRect();
}
//		소멸자:
CWindow::~CWindow()
{
	
}
//	윈도우 클래스를 생성하고 등록한다.
void	CWindow::initializeWindowClass()
{
	WNDCLASS wc = 
	{
		CS_VREDRAW|CS_HREDRAW|CS_OWNDC/*스타일*/, WndProc,
		0, 0, _hInstance, NULL/*아이콘*/, NULL/*커서*/, 
		(HBRUSH) 2/*배경색*/, NULL, DEFAULT_CWINDOW_WINDOW_CLASSNAME
	};
	RegisterClass(&wc);
	
}
//	윈도우객체를 생성한다
void	CWindow::initializeWindow()
{
	//	윈도우 생성:
	_hWnd = CreateWindow( DEFAULT_CWINDOW_WINDOW_CLASSNAME, DEFAULT_CWINDOW_WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,  DEFAULT_CWINDOW_WINDOW_X,  DEFAULT_CWINDOW_WINDOW_Y, 
		100, 100, NULL,NULL,
		_hInstance, NULL);	

	//	윈도우를 show:
	ShowWindow(_hWnd, _nCmdShow);
	UpdateWindow(_hWnd);
}
//	윈도우전체가 아닌, 그림이 출력되는 클라이언트영역이, ini 파일의 너비가 되게한다
void	CWindow::setClientRect()
{
	RECT crt;
	DWORD style, ex_style;
	SetRect(&crt, 0, 0, _ini->_graphic_width, _ini->_graphic_height); // RECT는 구조체이기에 이함수로 초기화시킨다

	style = GetWindowLong(_hWnd,GWL_STYLE);
	ex_style = GetWindowLong(_hWnd, GWL_EXSTYLE);
	AdjustWindowRectEx(&crt, style, GetMenu(_hWnd) != NULL, ex_style);
	if (style & WS_VSCROLL)
		crt.right += GetSystemMetrics(SM_CXVSCROLL);
	if (style & WS_HSCROLL)
		crt.bottom += GetSystemMetrics(SM_CYVSCROLL);

	SetWindowPos(_hWnd, NULL, 0, 0, crt.right - crt.left, crt.bottom - crt.top, SWP_NOMOVE | SWP_NOZORDER);		
}
//	메세지를 다룬다. 무한루프.
void	CWindow::HandleMessage()
{
	//	메세지가 도착했는지 확인(peek = 엿보다)
	//	getMessage를 사용하면, 메세지가 도착할때만 렌더링이 됨
	while ( _msg.message != WM_QUIT )
	{
		if ( PeekMessage(&_msg, NULL, 0U, 0U, PM_REMOVE) )
		{
			//	도착하면 메세지처리
			TranslateMessage(&_msg);
			DispatchMessage(&_msg);
		}
		else
		{
			//	한 프레임을 계산 및 출력한다
			_scripter->excute();
		}
	}
}
//	중복실행 방지
void	CWindow::isAlreadyExcuted()
{
	//	프로그램 이름과 동일한 윈도우가 이미 있는지 검사:
	HWND hWnd = FindWindow(NULL,  DEFAULT_CWINDOW_WINDOW_NAME);

	if (hWnd != NULL)
	{
		SetForegroundWindow(hWnd);
		ShowWindow(hWnd, SW_RESTORE);
		//	이 APP는 종료되야하기 때문에 에러를 throw한다
		throw CError 
		(	
			_T("에러00:\t중복실행으로, 프로그램을 종료합니다."), 
			_T("이 에러는 기록되지않습니다."),
			_T(__FUNCTION__),
			true // 메세지박스, 로그를 기록하지않는다
		);
	}
}