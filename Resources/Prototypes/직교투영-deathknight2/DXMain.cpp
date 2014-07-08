//버젼 정보
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 6
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
#include "defines.h"
#include ".\maingame.h"


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 6 전역변수
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
HINSTANCE				g_hInst;									//전역 인스턴스의 핸들선언
char  						g_ClassName[128] = "Narusia";		//클래스 이름
char  						g_WinName[128] = "Narusia";			//윈도우 이름
HWND					g_hWnd;									//윈도우의 핸들
LPDIRECT3D9			g_pD3D;
LPDIRECT3DDEVICE9	g_pd3dDevice;
CMainGame				g_MainGame;

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 6 함수
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
bool SetUp(char *szError);

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 6
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam, int nCmdShow)
{
	MSG			Message;		//메세지 구조체 선언
	WNDCLASS	WndClass;		//윈도우 클래스 선언
	g_hInst =	hInstance;		//인스턴스를 얻는다
	char			szError[128];

	WndClass.cbClsExtra		= 0;									//여분메모리	
	WndClass.cbWndExtra		= 0;									//여분메모리
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	//배경색상 지정
	WndClass.hCursor		= LoadCursor(NULL,IDC_ARROW);			//커서를 읽는다
	WndClass.hIcon			= LoadIcon(NULL,IDI_APPLICATION);		//아이콘을 읽는다
	WndClass.hInstance		= hInstance;							//윈도우 클래스의 인스턴스
	WndClass.lpfnWndProc	= (WNDPROC)WndProc;						//윈도우 프로시저의 이름
	WndClass.lpszClassName	= g_ClassName;							//윈도우 클래스의 이름
	WndClass.lpszMenuName	= NULL;									//메뉴의 이름
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;				//윈도우의 스타일
	RegisterClass(&WndClass);										//클래스를 등록한다

	//윈도우를 만든다
	g_hWnd = CreateWindow(g_ClassName, g_WinName, WS_POPUPWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, int(WINSIZEX), int(WINSIZEY),
		NULL, (HMENU)NULL, hInstance, NULL);
	if(SetUp(szError) == false)
	{
		MessageBox(g_hWnd, szError, "에러", MB_OK);
		return 0;
	}
	ShowWindow(g_hWnd, nCmdShow);

	while(true)
	{
        // 메시지큐에 메시지가 있으면 메시지 처리
		if( PeekMessage( &Message, NULL, 0U, 0U, PM_REMOVE ) )
		{
			if(Message.message == WM_QUIT) break;
			TranslateMessage( &Message );
			DispatchMessage( &Message );
		}
		// 처리할 메시지가 없으면 Render()함수 호출
		else g_MainGame.Management();
		
	}
	return int(Message.wParam);
}


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 6
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch(iMessage)
	{
		case WM_KEYDOWN:
			switch(wParam)
			{
				case VK_ESCAPE:
					PostMessage( hWnd, WM_DESTROY, 0, 0L );
				break;
			}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 6 DX SetUp
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
bool SetUp(char *szError)
{
	//인터페이스 생성
	if(NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		strcpy(szError, "장치 설정 실패");
		return false;
	}

	//디바이스 만들기위해서 구조체 값 입력
	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory(&d3dpp, sizeof(d3dpp));
#ifdef FULLMODE
	d3dpp.BackBufferWidth = WINSIZEX;
	d3dpp.BackBufferHeight = WINSIZEY;
	d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = false;
	// 비디오카드의 성능대로 프레임스를 나오게한다.
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	
	//z버퍼를 다이렉트엑스가 관리하겠다 
	d3dpp.EnableAutoDepthStencil	= true;
	//EnableAutoDepthStencil 트루일때만 의미 가있는것
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;
#else
	d3dpp.BackBufferWidth = WINSIZEX;
	d3dpp.BackBufferHeight = WINSIZEY;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = true;
	// 비디오카드의 성능대로 프레임스를 나오게한다.
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	
	//z버퍼를 다이렉트엑스가 관리하겠다 
	d3dpp.EnableAutoDepthStencil	= true;
	//EnableAutoDepthStencil 트루일때만 의미 가있는것
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;
#endif

	//디바이스를 만든다
	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice ) ) )
	{
		strcpy(szError, "디바이스 설정 실패");
		return false;     
	}

	//컬링모드
	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	//조명 끈다
	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	//z버퍼 설정
	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	g_MainGame.SetUp(g_pd3dDevice);
	return true;
}

