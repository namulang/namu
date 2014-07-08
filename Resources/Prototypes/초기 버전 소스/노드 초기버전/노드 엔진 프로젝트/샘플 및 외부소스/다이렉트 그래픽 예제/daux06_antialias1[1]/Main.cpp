// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }



CMain::CMain()
{
	m_pD3DXFont	= NULL;
}


INT CMain::Init()
{
	HRESULT hr=-1;

	D3DXFONT_DESC hFont =
	{
		16, 0
		, FW_BOLD, 1, FALSE
		, HANGUL_CHARSET
		, OUT_DEFAULT_PRECIS
		, ANTIALIASED_QUALITY, FF_DONTCARE
		, "Arial"
	};

	if( FAILED( hr = D3DXCreateFontIndirect( m_pd3dDevice, &hFont, &m_pD3DXFont ) ) )
		return -1;


	m_pVtx[0]	= VtxD(-1.0f, 0.0f, 0.0f, 0xffff0000);
	m_pVtx[1]	= VtxD( 0.0f, 1.0f, 0.0f, 0xff00ff00);
	m_pVtx[2]	= VtxD( 1.0f, 0.0f, 0.0f, 0xff0000ff);
	m_pVtx[3]	= VtxD( 0.0f,-1.0f, 0.0f, 0xffFF00FF);
	
	return 0;
}

void CMain::Destroy()
{
	SAFE_RELEASE(	m_pD3DXFont	);
}

INT CMain::FrameMove()
{
	D3DXMATRIX m_mtViw;
	D3DXVECTOR3 vEyePt( 0.0f, 0.0f,-2.2f );
	D3DXVECTOR3 vLookAt( 0.0f,0.0f, 0.0f );	
	D3DXVECTOR3 vUpVec( -1.4f, 1.0f, 0.0f );
	D3DXMatrixLookAtLH(&m_mtViw, &vEyePt, &vLookAt, &vUpVec );

	m_pd3dDevice->SetTransform( D3DTS_VIEW, &m_mtViw );

	
	// 투영 행렬
	D3DXMATRIX m_mtPrj;
	FLOAT	fScreenW = (FLOAT)800;
	FLOAT	fScreenH = (FLOAT)600;
	FLOAT	fFOV	= D3DX_PI/4.0f;
	FLOAT	fAspect	= fScreenW/fScreenH;
	FLOAT	fNear	= 1.f;
	FLOAT	fFar	= 5000.f;
	
	D3DXMatrixPerspectiveFovLH(&m_mtPrj, fFOV, fAspect, fNear, fFar);
	m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &m_mtPrj );
	

	return 0;
}


void CMain::Render()
{
	if( NULL == m_pd3dDevice )
		return;
	
	m_pd3dDevice->Clear( 0, NULL, (D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER), D3DCOLOR_XRGB(0,128,200), 1.0f, 0 );
	
	if(FAILED( m_pd3dDevice->BeginScene() ) )
		return;


	// Anti-Aliasing 해제
	if(::GetAsyncKeyState(VK_F2) &0x8000)
	{
		m_pd3dDevice->SetRenderState (D3DRS_MULTISAMPLEANTIALIAS, FALSE);
		m_pd3dDevice->SetRenderState (D3DRS_ANTIALIASEDLINEENABLE, FALSE);
	}

	if(::GetAsyncKeyState(VK_F3) &0x8000)
	{
		m_pd3dDevice->SetRenderState (D3DRS_MULTISAMPLEANTIALIAS, TRUE);
		m_pd3dDevice->SetRenderState (D3DRS_ANTIALIASEDLINEENABLE, TRUE);
	}


	
	m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	

	m_pd3dDevice->SetFVF(VtxD::FVF);
	m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_pVtx, sizeof(VtxD));



	RECT rct={ 10, 10, 800 - 20, 10+30};
	char	sMsg[256]={0};
	sprintf(sMsg, "FPS: %12.lf", m_fFps);
	m_pD3DXFont->DrawText(NULL, sMsg, -1, &rct, 0, D3DXCOLOR(1,1,0,1) );

	
	m_pd3dDevice->EndScene();
}


LRESULT CMain::MsgProc( HWND m_hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
		case WM_PAINT:
			break;
	}
	
	return CD3DApp::MsgProc( m_hWnd, msg, wParam, lParam );
}
