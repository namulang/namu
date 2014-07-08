#include ".\maingame.h"

CMainGame::CMainGame(void)
{	
	m_dwNowTime = 0;
	m_dwColor = 0x88000000;
}

CMainGame::~CMainGame(void)
{
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 9  셋업
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
BOOL CMainGame::SetUp(LPDIRECT3DDEVICE9 Device)
{
	// 장치 옮기기
	m_pDevice = Device;

	m_Image[0].Setting(TRUE, TRUE, 1);
	m_Image[1].Setting(TRUE, FALSE, 0);
	
	CUSTOMVERTEX Vertex[] = 
	{
		{-0.1f, -0.1f, 0.0f, 0xffffffff, 0.0f, 1.0f	},
		{-0.1f,  0.1f, 0.0f, 0xffffffff, 0.0f, 0.0f	},
		{ 0.1f,  0.1f, 0.0f, 0xffffffff, 1.0f, 0.0f	},
		{ 0.1f, -0.1f, 0.0f, 0xffffffff, 1.0f, 1.0f	},
	};
	tagIndex Indices[] =
	{
		{0, 1, 2},
		{0, 2, 3},
	};

	NONETEXTUREVERTEX Vertex2[COOLTIME_MAX_DIVIDE] =
	{
		{ 0.0f,  0.0f, -5.0f, 0xffffffff},
	};

	tagIndex Indices2[COOLTIME_MAX_DIVIDE - 1];
	// 버텍스 루프로 만든다.
	for(int i = 1; i < COOLTIME_MAX_DIVIDE; i++)
	{
		Vertex2[i].x = float(cosf( (D3DX_PI * 2) / (COOLTIME_MAX_DIVIDE - 2) * (i - 1)) ) * 1.0f;
		Vertex2[i].y = float(sinf( (D3DX_PI * 2) /  (COOLTIME_MAX_DIVIDE - 2) * (i - 1)) ) * 1.0f;
		Vertex2[i].z = -5.0f;
		Vertex2[i].color = 0xffffffff;
	}
	// 인덱스 루프를 돈다.
	for(int i = 0; i < COOLTIME_MAX_DIVIDE - 2; i++)
	{	
		Indices2[i]._0 = 0;
		Indices2[i]._1 = i +1;
		Indices2[i]._2 = i +2;
	}

	m_Image[0].VertexBufferSetUp(m_pDevice, 4, Vertex);
	m_Image[0].IndexBufferSetUp(m_pDevice, 2, Indices);
	m_Image[0].TextureSetUp(m_pDevice, "image\\1.jpg", 0);

	m_Image[1].NoneTextureVertexBufferSetUp(m_pDevice, COOLTIME_MAX_DIVIDE, Vertex2);
	m_Image[1].IndexBufferSetUp(m_pDevice, COOLTIME_MAX_DIVIDE - 2, Indices2);

	CameraSetUp();
	// 인풋 셋업
	InputSetUp();
	m_Axis.Setup(m_pDevice);
	return true;
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 9  PeekMessage 루프
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CMainGame::Management(void)
{
	// 마우스 키보드 실시간 업데이트 와 카메라 무빙
	KeyBordMouseCameraUpdate();
	// 랜더링
	Render();
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 9  랜더링
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CMainGame::Render(void)
{
	//백버퍼 초기화
	m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

	if(SUCCEEDED( m_pDevice->BeginScene() ) )
	{
		static int nCount = 0;
		m_dwTime = GetTickCount();
		D3DXMATRIXA16 mTran;

		////땅
		//SetMatrics();
		D3DXMATRIXA16 m_RotYawPitchRoll;
		D3DXMATRIXA16 g_matWorld;
		D3DXMatrixIdentity(&g_matWorld);
		m_pDevice->SetTransform( D3DTS_WORLD, &g_matWorld );

		m_Image[0].Render(m_pDevice, 0);

		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		m_pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, m_dwColor);
		m_pDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
		m_pDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_CURRENT );
		m_pDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2,  D3DTA_TFACTOR  );
		m_Image[1].RenderCoolTime(m_pDevice);
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		m_Axis.Render();
		D3DXMATRIXA16 mScale;

		D3DXMatrixScaling(&mScale, 1000.0f, 1000.0f, 1000.0f);
		g_matWorld = g_matWorld * mScale;
				m_pDevice->SetTransform( D3DTS_WORLD, &g_matWorld );
		m_Image[0].Render(m_pDevice, 0);
	
		m_pDevice->EndScene();
	}
	//백버퍼를 화면에 출력한다
	m_pDevice->Present( NULL, NULL, NULL, NULL );
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 9  카메라 셋업
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CMainGame::CameraSetUp(void)
{
	// 카메라 셋업
	m_Camera.SetPosition(&D3DXVECTOR3(0.0f, 0.0f, -10.0f));
	m_Camera.Update(m_pDevice);
	m_Camera.SetUpProjection(m_pDevice, D3DX_PI/4.0f, WINSIZEX/WINSIZEY, 1.0f, 1000.0f );
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 9  인풋 셋업
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
BOOL CMainGame::InputSetUp(void)
{
	// 인풋 셋업
	if( FAILED( DirectInput8Create( g_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, NULL ) ) )
	{
		MessageBox(g_hWnd, "Direct Input Create Error", "에러", MB_OK);
		return FALSE;
	}
	if(!m_InputMouse.Initialize(m_pDI, g_hWnd, DIT_MOUSE))
	{
		MessageBox(g_hWnd, "마우스 인풋 설치 실패", "에러", MB_OK);
		return FALSE;
	}
	if(!m_InputKeyBoard.Initialize(m_pDI, g_hWnd, DIT_KEYBOARD))
	{
		MessageBox(g_hWnd, "키보드 인풋 설치 실패", "에러", MB_OK);
		return FALSE;
	}
	return TRUE;
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 9  마우스 키보드 실시간 업데이트 와 카메라 무빙
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CMainGame::KeyBordMouseCameraUpdate(void)
{

	// 인풋 키를 받아온다.
	BOOL* pPressedKeys = m_InputKeyBoard.GetKeys();
	BOOL* pMouseButtons = m_InputMouse.GetButtons();

	if ( pMouseButtons[0] )
	{
		m_Camera.UpdateYallPitchRoll( m_InputMouse.GetXDelta() * D3DXToRadian(1) * MouseFLOAT, 0.0f, 0.0f);
		m_Camera.UpdateYallPitchRoll( 0.0f, m_InputMouse.GetYDelta()* D3DXToRadian(1) * MouseFLOAT, 0.0f);
	}
	if ( pMouseButtons[1] )
	{
		m_Camera.UpdateYallPitchRoll( m_InputMouse.GetXDelta() * D3DXToRadian(1) * MouseFLOAT, 0.0f, 0.0f);
		m_Camera.UpdateYallPitchRoll( 0.0f, m_InputMouse.GetYDelta()* D3DXToRadian(1) * MouseFLOAT, 0.0f);
		m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	if(m_InputMouse.GetZDelta() > 0)
	{
		m_Camera.Fly(MovingSpeed * 3);
	}
	if(m_InputMouse.GetZDelta() < 0)
	{
		m_Camera.Fly(-MovingSpeed * 3);
	}
	if(pPressedKeys[DIK_W])
	{
		m_Camera.Walk(MovingSpeed / 3);		
	}
	if(pPressedKeys[DIK_S])
	{
		m_Camera.Walk(-MovingSpeed / 3);
	}
	if(pPressedKeys[DIK_Q])
	{
		m_Camera.Strafe(-MovingSpeed / 3);
	}
	if(pPressedKeys[DIK_E])
	{
		m_Camera.Strafe(MovingSpeed / 3);
	}
	if(pPressedKeys[DIK_A])
	{
		m_Camera.UpdateYallPitchRoll( -D3DXToRadian(MovingSpeed), 0.0f, 0.0f);
	}
	if(pPressedKeys[DIK_D])
	{
		m_Camera.UpdateYallPitchRoll( D3DXToRadian(MovingSpeed), 0.0f, 0.0f);
	}

	if(pPressedKeys[DIK_SPACE])
	{
		m_dwColor = 0x55000000;
	}
	else
	{
		m_dwColor = 0x88000000;
	}
	m_Camera.Update(m_pDevice);
	m_InputKeyBoard.Read();
	m_InputMouse.Read();
}
