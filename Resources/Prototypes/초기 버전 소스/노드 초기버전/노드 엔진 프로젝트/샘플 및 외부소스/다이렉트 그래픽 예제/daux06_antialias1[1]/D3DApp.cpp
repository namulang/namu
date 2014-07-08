// Implementation of the CD3DApp class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CD3DApp* CD3DApp::g_pD3DApp = NULL;


CD3DApp::CD3DApp()
{
	CD3DApp::g_pD3DApp = this;

	m_pD3D			= NULL;
	m_pd3dDevice	= NULL;

	memset(&m_d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));

	m_fFps			= 0;
}



INT CD3DApp::Create( HINSTANCE hInst)
{
	m_hInst	= hInst;

	WNDCLASS wc =
	{
		(CS_CLASSDC | CS_DBLCLKS)
			, WndProc
			, 0L
			, 0L
			, m_hInst
			, LoadIcon(NULL, IDI_APPLICATION)
			, LoadCursor(NULL, IDC_ARROW)
			, (HBRUSH)GetStockObject(WHITE_BRUSH)
			, NULL
			, "Anti-Aliasing"
	};
	
	RegisterClass( &wc );
	
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE;
	RECT rc={0,0, 800, 600};
	AdjustWindowRect( &rc, dwStyle, FALSE);
	
	
	// 윈도우 생성
	m_hWnd = CreateWindow( "Anti-Aliasing"
		, "Anti-Aliasing"
		, dwStyle
		, 100
		, 100
		, (rc.right-rc.left)
		, (rc.bottom-rc.top)
		, GetDesktopWindow()
		, NULL
		, m_hInst
		, NULL );
	
	

	if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return -1;
	
	
	D3DDISPLAYMODE d3ddm;
	if( FAILED( m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
		return -1;
	
	
//	m_d3dpp.BackBufferFormat		= d3ddm.Format;
	m_d3dpp.BackBufferFormat		= D3DFMT_X8R8G8B8;
	m_d3dpp.BackBufferCount			= 1;
	
	m_d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	m_d3dpp.hDeviceWindow			= m_hWnd;
	m_d3dpp.Windowed				= TRUE;
	
	m_d3dpp.EnableAutoDepthStencil	= TRUE;
	m_d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;

	m_d3dpp.FullScreen_RefreshRateInHz	= 0;
    m_d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;


	
	DWORD dQualityLevels;
	for(int nType=D3DMULTISAMPLE_16_SAMPLES; nType>=0; --nType)
	{
		if(SUCCEEDED(m_pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT
												, D3DDEVTYPE_HAL
												, m_d3dpp.BackBufferFormat
												, TRUE
												, (D3DMULTISAMPLE_TYPE)nType
												, &dQualityLevels)))
		{
			m_d3dpp.MultiSampleType = (D3DMULTISAMPLE_TYPE)nType;
			m_d3dpp.MultiSampleQuality = dQualityLevels-1;

			break;
		}
	}



	if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT
									, D3DDEVTYPE_HAL
									, m_hWnd
									, D3DCREATE_SOFTWARE_VERTEXPROCESSING
									, &m_d3dpp
									, &m_pd3dDevice ) ) )
	{
		return -1;
	}
	
	
	if(FAILED(Init()))
		return -1;
	
	ShowWindow( m_hWnd, SW_SHOWDEFAULT );
	UpdateWindow( m_hWnd );
	
	
	return S_OK;
}


void CD3DApp::Cleanup()
{
	Destroy();
	
	if( m_pd3dDevice != NULL) 
		m_pd3dDevice->Release();
	
	if( m_pD3D != NULL)
		m_pD3D->Release();
}


LRESULT WINAPI CD3DApp::WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	if(CD3DApp::g_pD3DApp)
		return g_pApp->MsgProc(hWnd, msg, wParam, lParam);

	return  DefWindowProc( hWnd, msg, wParam, lParam );
}


LRESULT CD3DApp::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_KEYDOWN:
	{
		if(VK_ESCAPE == wParam)
		{
			SendMessage(hWnd, WM_DESTROY, 0, 0);
			return 0;
		}

		break;
	}

	case WM_DESTROY:
		Cleanup();
		PostQuitMessage( 0 );
		return 0;
	}
	
	return DefWindowProc( hWnd, msg, wParam, lParam );
}



INT CD3DApp::Run()
{	    
	MSG msg={0};
	
	while( msg.message!=WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			if(FAILED(Render3D()))
				break;

			UpdateStats();
		}
	}
	
	return 0;
}


INT CD3DApp::Render3D()
{
	if(FAILED(FrameMove()))
		return -1;

	Render();

	return m_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}






void CD3DApp::UpdateStats()
{
	static INT				iCnt = 0;
	static LARGE_INTEGER	Freq = {0};
	static LARGE_INTEGER	dBgn = {0};
	static BOOL		bEnable=1;

	LARGE_INTEGER	dCur = {0};

	if(0 == bEnable)
		return;

	if(0 == Freq.QuadPart)														// 최초 함수 호출시
	{
		bEnable = QueryPerformanceFrequency( &Freq);

		if(0 == bEnable)
			return;

		QueryPerformanceCounter(&dBgn);
	}


	QueryPerformanceCounter(&dCur);
	++iCnt;

	if(iCnt>=30)
	{
		DOUBLE fElapsedTime = DOUBLE(dCur.QuadPart - dBgn.QuadPart)/ DOUBLE(Freq.QuadPart);
		m_fFps = iCnt/fElapsedTime;

		iCnt = 0;
		dBgn = dCur;
	}
}