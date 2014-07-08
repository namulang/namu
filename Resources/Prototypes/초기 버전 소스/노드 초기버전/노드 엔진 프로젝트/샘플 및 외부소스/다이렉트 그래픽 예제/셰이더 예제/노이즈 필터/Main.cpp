

#include "_StdAfx.h"


CMain::CMain()
:	m_pD3DXFont	(0)
,	m_pInput	(0)
,	m_pShader	(0)
{
}


HRESULT CMain::Init()
{
	SAFE_NEWCREATE1(m_pInput , CMcInput		, m_hWnd);
	SAFE_NEWCREATE1(m_pShader, CShaderEx	, m_pd3dDevice);

	
	D3DXFONT_DESC hFont =
	{
		16, 0
		, FW_NORMAL
		, 1
		, FALSE
		, HANGUL_CHARSET
		, OUT_DEFAULT_PRECIS
		, ANTIALIASED_QUALITY
		, FF_DONTCARE
		, "Arial"
	};

	if( FAILED( D3DXCreateFontIndirect(m_pd3dDevice, &hFont, &m_pD3DXFont ) ) )
		return -1;

	return S_OK;
}


HRESULT CMain::Destroy()
{
	SAFE_RELEASE( m_pD3DXFont );

	SAFE_DELETE(	m_pInput	);

	SAFE_DELETE(	m_pShader	);

	return S_OK;
}



HRESULT CMain::Restore()
{
	if(m_pD3DXFont)
		m_pD3DXFont->OnResetDevice();


	m_pShader->Restore();
	
	return S_OK;
}


HRESULT CMain::Invalidate()
{
	if(m_pD3DXFont)
		m_pD3DXFont->OnLostDevice();


	m_pShader->Invalidate();

	return S_OK;
}




HRESULT CMain::FrameMove()
{
	SAFE_FRMOV(	m_pInput	);

	// Wheel mouse...
	D3DXVECTOR3 vcD = m_pInput->GetMouseEps();


	SAFE_FRMOV(	m_pShader	);

	sprintf( m_sMsg, "%s %s", m_strDeviceStats, m_strFrameStats	);

	return S_OK;
}


HRESULT CMain::Render()
{
	HRESULT hr=0;

	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;


	m_pd3dDevice->Clear( 0L
						, NULL
						, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL
						, 0x00006699
						, 1.0f
						, 0L
						);


	// ½¦ÀÌ´õ ½ÇÇà
	SAFE_RENDER(	m_pShader	);
	
	
	m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE);
	m_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE , FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pd3dDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	
	RECT	rc;
	SetRect(&rc, 5, 5, m_d3dsdBackBuffer.Width - 20, 30);
	m_pD3DXFont->DrawText(NULL, m_sMsg, -1, &rc, 0, D3DCOLOR_ARGB(255,255,255,0));

	m_pd3dDevice->EndScene();
	
	return S_OK;
}



LRESULT CMain::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	if(m_pInput)
		m_pInput->MsgProc(hWnd, msg, wParam, lParam);

	switch( msg )
	{
		case WM_PAINT:
		{
			
			break;
		}
		
	}
	
	return CD3DApplication::MsgProc( hWnd, msg, wParam, lParam );
}