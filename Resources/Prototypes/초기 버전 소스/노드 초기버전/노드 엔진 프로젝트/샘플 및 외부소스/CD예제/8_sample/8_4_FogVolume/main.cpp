//-------------------------------------------------------------
// File: main.cpp
//
// Desc: º¼·ýÆ÷±×
//-------------------------------------------------------------
#define STRICT
#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <basetsd.h>
#include <math.h>
#include <stdio.h>
#include <d3dx9.h>
#include <dxerr9.h>
#include <tchar.h>
#include "DXUtil.h"
#include "D3DEnumeration.h"
#include "D3DSettings.h"
#include "D3DApp.h"
#include "D3DFont.h"
#include "D3DFile.h"
#include "D3DUtil.h"
#include "resource.h"
#include "main.h"


//-------------------------------------------------------------
// Àü¿ªº¯¼ö
//-------------------------------------------------------------
CMyD3DApplication* g_pApp  = NULL;
HINSTANCE          g_hInst = NULL;


//-------------------------------------------------------------
// Name: WinMain()
// Desc: ¸ÞÀÎÇÔ¼ö
//-------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
    CMyD3DApplication d3dApp;

    g_pApp  = &d3dApp;
    g_hInst = hInst;

    InitCommonControls();
    if( FAILED( d3dApp.Create( hInst ) ) )
        return 0;

    return d3dApp.Run();
}




//-------------------------------------------------------------
// Name: CMyD3DApplication()
// Desc: ¾îÇÃ¸®ÄÉÀÌ¼Ç »ý¼ºÀÚ
//-------------------------------------------------------------
CMyD3DApplication::CMyD3DApplication()
{
	m_pMesh						= new CD3DMesh();
	m_pMeshBg					= new CD3DMesh();
	m_pDecl						= NULL;
	m_pEffect					= NULL;
	m_hmWVP						= NULL;
	m_hmWVPT					= NULL;
	m_hvCol						= NULL;
	m_hvDir						= NULL;

	m_pMapZ						= NULL;
	m_pColorMap					= NULL;
	m_pColorMapSurf				= NULL;
	m_pDepthMap					= NULL;
	m_pDepthMapSurf				= NULL;
	m_pFogMap					= NULL;
	m_pFogMapSurf				= NULL;

	m_zoom						= 5.0f;
    m_fWorldRotX                = -0.8f;
	m_fWorldRotY                = 0;

	m_dwCreationWidth           = 500;
    m_dwCreationHeight          = 375;
    m_strWindowTitle            = TEXT( "main" );
    m_d3dEnumeration.AppUsesDepthBuffer   = TRUE;
	m_bStartFullscreen			= false;
	m_bShowCursorWhenFullscreen	= false;

    m_pFont                     = new CD3DFont( _T("Arial"), 12, D3DFONT_BOLD );
    m_bLoadingApp               = TRUE;
    
	ZeroMemory( &m_UserInput, sizeof(m_UserInput) );
}




//-------------------------------------------------------------
// Name: ~CMyD3DApplication()
// Desc: ¼Ò¸êÀÚ
//-------------------------------------------------------------
CMyD3DApplication::~CMyD3DApplication()
{
}




//-------------------------------------------------------------
// Name: OneTimeSceneInit()
// Desc: ´Ü ÇÑ¹ø¸¸ ÃÊ±âÈ­
//       À©µµ¿ì ÃÊ±âÈ­¿Í IDirect3D9ÃÊ±âÈ­´Â ³¡³­µÚ
//       ±×·¯³ª LPDIRECT3DDEVICE9ÃÊ±âÈ­´Â ³¡³ªÁö ¾ÊÀº »óÅÂ
//-------------------------------------------------------------
HRESULT CMyD3DApplication::OneTimeSceneInit()
{
    // ·Îµù ¸Þ½ÃÁö Ãâ·Â
    SendMessage( m_hWnd, WM_PAINT, 0, 0 );

    m_bLoadingApp = FALSE;

    return S_OK;
}




//-------------------------------------------------------------
// Name: ConfirmDevice()
// Desc: ÃÊ±âÈ­½Ã È£ÃâµÊ. ÇÊ¿äÇÑ ´É·Â(caps)Ã¼Å©
//-------------------------------------------------------------
HRESULT CMyD3DApplication::ConfirmDevice( D3DCAPS9* pCaps
						, DWORD dwBehavior, D3DFORMAT Format )
{
    UNREFERENCED_PARAMETER( Format );
    UNREFERENCED_PARAMETER( dwBehavior );
    UNREFERENCED_PARAMETER( pCaps );
    
	// ¼ÎÀÌ´õÃ¼Å©
	if( pCaps->VertexShaderVersion < D3DVS_VERSION(1,1) &&
	  !(dwBehavior & D3DCREATE_SOFTWARE_VERTEXPROCESSING ) )
		return E_FAIL;	// Á¤Á¡¼ÎÀÌ´õ
	
	if( pCaps->PixelShaderVersion < D3DPS_VERSION(2,0))
		return E_FAIL;	// ÇÈ¼¿¼ÎÀÌ´õ

	// MRT(Multiple Render Target)¸¦ 2Àå »ç¿ëÇÑ´Ù
	if(pCaps->NumSimultaneousRTs < 2) return E_FAIL;

	return S_OK;
}


//-------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc: µð¹ÙÀÌ½º°¡ »ý¼ºµÈÈÄÀÇ ÃÊ±âÈ­
//       ÇÁ·¹ÀÓ¹öÆÛ Æ÷¸Ë°ú µð¹ÙÀÌ½º Á¾·ù°¡ º¯ÇÑµÚ¿¡ È£Ãâ
//       ¿©±â¼­ È®º¸ÇÑ ¸Þ¸ð¸®´Â DeleteDeviceObjects()¿¡¼­ ÇØÁ¦
//-------------------------------------------------------------
HRESULT CMyD3DApplication::InitDeviceObjects()
{
    HRESULT hr;

    // ¸Þ½ÃÀÐ±â
	if( FAILED( hr=m_pMesh->Create( m_pd3dDevice, "ufo.x" )))
        return DXTRACE_ERR( "Load Mesh", hr );
	m_pMesh->UseMeshMaterials(FALSE);// ÅØ½ºÃ³¸¦ Á÷Á¢¼³Á¤
	m_pMesh->SetFVF( m_pd3dDevice, D3DFVF_XYZ | D3DFVF_NORMAL );

    // ¸Þ½ÃÀÐ±â
	if( FAILED( hr=m_pMeshBg->Create( m_pd3dDevice, "map.x" )))
        return DXTRACE_ERR( "Load Mesh", hr );
	m_pMeshBg->UseMeshMaterials(FALSE);// ÅØ½ºÃ³¸¦ Á÷Á¢¼³Á¤
	m_pMeshBg->SetFVF( m_pd3dDevice, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 );

	// Á¤Á¡¼±¾ð ¿ÀºêÁ§Æ® »ý¼º
	D3DVERTEXELEMENT9 decl[] =
	{
		{0,  0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,	0},
		{0, 24, D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};
	if( FAILED( hr = m_pd3dDevice->CreateVertexDeclaration( decl, &m_pDecl )))
		return DXTRACE_ERR ("CreateVertexDeclaration", hr);

	
	// ¼ÎÀÌ´õÀÐ±â
    if( FAILED( hr = D3DXCreateEffectFromFile(
						m_pd3dDevice, "hlsl.fx", NULL, NULL, 
						0, NULL, &m_pEffect, NULL ) ) )
		return DXTRACE_ERR( "CreateEffectFromFile", hr );
	m_hmWVP  = m_pEffect->GetParameterByName( NULL, "mWVP" );
	m_hmWVPT = m_pEffect->GetParameterByName( NULL, "mWVPT" );
	m_hvCol  = m_pEffect->GetParameterByName( NULL, "vCol" );
	m_hvDir  = m_pEffect->GetParameterByName( NULL, "vLightDir" );

    m_pFont->InitDeviceObjects( m_pd3dDevice );// ÆùÆ®
    
	return S_OK;
}

//-------------------------------------------------------------
// Name: RestoreDeviceObjects()
// Desc: È­¸éÅ©±â°¡ º¯ÇßÀ»¶§ È£ÃâµÊ
//       È®º¸ÇÑ ¸Þ¸ð¸®´Â InvalidateDeviceObjects()¿¡¼­ ÇØÁ¦
//-------------------------------------------------------------
HRESULT CMyD3DApplication::RestoreDeviceObjects()
{
	D3DVIEWPORT9 viewport;
	
	// »õ·Ó°Ô ¼³Á¤ÇÑ ºäÆ÷Æ®·ÎºÎÅÍ ÅØ½ºÃ³¸¦ Àç±¸¼º
	m_pd3dDevice->GetViewport(&viewport);
	m_Width  = viewport.Width;
	m_Height = viewport.Height;
	// ÅØ½ºÃ³Å©±â´Â ºäÆ÷Æ®Å©±â ÀÌ»óÀÇ 2^n
	for( m_MapW=1 ; m_MapW<m_Width  ; m_MapW*=2 );
	for( m_MapH=1 ; m_MapH<m_Height ; m_MapH*=2 );

	// ·»´õ¸µÅ¸°ÙÀÇ ±íÀÌ¹öÆÛ »ý¼º
	if (FAILED(m_pd3dDevice->CreateDepthStencilSurface(m_MapW, m_MapH, 
		D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &m_pMapZ, NULL)))
		return E_FAIL;
	// ÄÃ·¯¹öÆÛ
	if (FAILED(m_pd3dDevice->CreateTexture( m_MapW, m_MapH, 1, 
		D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pColorMap, NULL)))
		return E_FAIL;
	if (FAILED(m_pColorMap->GetSurfaceLevel(0, &m_pColorMapSurf)))
		return E_FAIL;
	// ±íÀÌ¹öÆÛ
	if (FAILED(m_pd3dDevice->CreateTexture(m_MapW, m_MapH, 1, 
		D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT, &m_pDepthMap, NULL)))
		return E_FAIL;
	if (FAILED(m_pDepthMap->GetSurfaceLevel(0, &m_pDepthMapSurf)))
		return E_FAIL;
	// Æ÷±×¹öÆÛ
	if (FAILED(m_pd3dDevice->CreateTexture(m_MapW, m_MapH, 1, 
		D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT, &m_pFogMap, NULL)))
		return E_FAIL;
	if (FAILED(m_pFogMap->GetSurfaceLevel(0, &m_pFogMapSurf)))
		return E_FAIL;


	// ´ÜÃà¸ÅÅ©·Î
	#define RS   m_pd3dDevice->SetRenderState
	#define SAMP m_pd3dDevice->SetSamplerState

    // ·»´õ¸µ »óÅÂ¼³Á¤
    RS  ( D3DRS_ZENABLE,        TRUE );
    RS  ( D3DRS_LIGHTING,       FALSE );

    // ÅØ½ºÃ³ »óÅÂ¼³Á¤
	SAMP( 0, D3DSAMP_ADDRESSU,  D3DTADDRESS_CLAMP );
	SAMP( 0, D3DSAMP_ADDRESSV,  D3DTADDRESS_CLAMP );
    SAMP( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    SAMP( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

    // ¿ùµåÇà·Ä
    D3DXMatrixIdentity( &m_mWorld );

	// ºäÇà·Ä
    D3DXVECTOR3 vFrom   = D3DXVECTOR3( 0.0f, 0.0f, -m_zoom );
    D3DXVECTOR3 vLookat = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUp     = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &m_mView, &vFrom, &vLookat, &vUp );

    // Åõ¿µÇà·Ä
    FLOAT fAspect = ((FLOAT)m_d3dsdBackBuffer.Width )
				  / ((FLOAT)m_d3dsdBackBuffer.Height);
    D3DXMatrixPerspectiveFovLH( &m_mProj, D3DX_PI/4, fAspect
								, 1.0f, 100.0f );

	// ±¤¿ø¹æÇâ ¼³Á¤
	m_LightDir = D3DXVECTOR4(-0.6f, 0.6f, -0.6f, 0.3f);
	
	m_pMesh  ->RestoreDeviceObjects(m_pd3dDevice);
	m_pMeshBg->RestoreDeviceObjects(m_pd3dDevice);
	if( m_pEffect!=NULL ) m_pEffect->OnResetDevice();// ¼ÎÀÌ´õ

    m_pFont->RestoreDeviceObjects();	// ÆùÆ®

    return S_OK;
}




//-------------------------------------------------------------
// Name: FrameMove()
// Desc: ¸Å ÇÁ·¹ÀÓ¸¶´Ù È£ÃâµÊ. ¾Ö´Ï¸ÞÀÌ¼Ç Ã³¸®µî ´ã´ç
//-------------------------------------------------------------
HRESULT CMyD3DApplication::FrameMove()
{
	UpdateInput( &m_UserInput ); // ÀÔ·Âµ¥ÀÌÅÍ °»½Å

	//---------------------------------------------------------
	// ÀÔ·Â¿¡ µû¶ó ÁÂÇ¥°è¸¦ °»½ÅÇÑ´Ù
	//---------------------------------------------------------
	// È¸Àü
    if( m_UserInput.bRotateLeft && !m_UserInput.bRotateRight )
        m_fWorldRotY += m_fElapsedTime;
    else if( m_UserInput.bRotateRight && !m_UserInput.bRotateLeft )
        m_fWorldRotY -= m_fElapsedTime;

    if( m_UserInput.bRotateUp && !m_UserInput.bRotateDown )
        m_fWorldRotX += m_fElapsedTime;
    else if( m_UserInput.bRotateDown && !m_UserInput.bRotateUp )
        m_fWorldRotX -= m_fElapsedTime;
	// ÁÜ
	if(m_UserInput.bZ && !m_UserInput.bX)
		m_zoom += 0.01f;
	else if(m_UserInput.bX && !m_UserInput.bZ)
		m_zoom -= 0.01f;


	//---------------------------------------------------------
	// Çà·Ä°»½Å
	//---------------------------------------------------------
 	D3DXMATRIX matRotX, matRotY;
    D3DXMatrixRotationX( &matRotX, m_fWorldRotX );
    D3DXMatrixRotationY( &matRotY, m_fWorldRotY );
    D3DXMatrixMultiply( &m_mWorld, &matRotY, &matRotX );

    D3DXVECTOR3 vFrom   = D3DXVECTOR3( 0.0f, 0.0f, -m_zoom );
    D3DXVECTOR3 vLookat = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUp     = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &m_mView, &vFrom, &vLookat, &vUp );

	return S_OK;
}




//-------------------------------------------------------------
// Name: UpdateInput()
// Desc: ÀÔ·Âµ¥ÀÌÅÍ °»½Å
//-------------------------------------------------------------
void CMyD3DApplication::UpdateInput( UserInput* pUserInput )
{
    pUserInput->bRotateUp    = ( m_bActive && (GetAsyncKeyState( VK_UP )    & 0x8000) == 0x8000 );
    pUserInput->bRotateDown  = ( m_bActive && (GetAsyncKeyState( VK_DOWN )  & 0x8000) == 0x8000 );
    pUserInput->bRotateLeft  = ( m_bActive && (GetAsyncKeyState( VK_LEFT )  & 0x8000) == 0x8000 );
    pUserInput->bRotateRight = ( m_bActive && (GetAsyncKeyState( VK_RIGHT ) & 0x8000) == 0x8000 );
	pUserInput->bZ = ( m_bActive && (GetAsyncKeyState( 'Z' ) & 0x8000) == 0x8000 );
	pUserInput->bX = ( m_bActive && (GetAsyncKeyState( 'X' ) & 0x8000) == 0x8000 );
}




//-------------------------------------------------------------
// Name: Render()
// Desc: È­¸é ·»´õ
//-------------------------------------------------------------
HRESULT CMyD3DApplication::Render()
{
 	LPDIRECT3DSURFACE9 pOldBackBuffer, pOldZBuffer;
	D3DVIEWPORT9 oldViewport;
	D3DXHANDLE hTechnique;
	D3DXMATRIX m, mL, mWT;
	D3DXVECTOR4 v;
	DWORD i;
	FLOAT ds = 0.5f/(FLOAT)m_MapW;// ÅØ¼¿Áß½É ÀÌµ¿¿ë
	FLOAT dt = 0.5f/(FLOAT)m_MapH;
	FLOAT s = (FLOAT)m_Width /(FLOAT)m_MapW + ds;
	FLOAT t = (FLOAT)m_Height/(FLOAT)m_MapH + dt;
	// Åõ¿µ°ø°£¿¡¼­ ÅØ½ºÃ³ÁÂÇ¥·Î ÀÌµ¿ÇÏ´Â º¯È¯Çà·Ä
	D3DXMATRIX	mT = D3DXMATRIX(
						0.5f*s, 0.0f  ,0.0f,0.0f,
						0.0f  ,-0.5f*t,0.0f,0.0f,
						0.0f  , 0.0f  ,1.0f,0.0f,
						0.5f*s, 0.5f*t,0.0f,1.0f);
	// º¯È¯¿ëºäÆ÷Æ®          x y  width   height   minz maxz
	D3DVIEWPORT9 viewport = {0,0, m_Width,m_Height,0.0f,1.0f};

    if( SUCCEEDED( m_pd3dDevice->BeginScene()))	// ·»´õ ½ÃÀÛ
    {
		if(m_pEffect != NULL)
		{
			//-------------------------------------------------
			// ·»´õ¸µÅ¸°Ù º¸Á¸
			//-------------------------------------------------
			m_pd3dDevice->GetRenderTarget(0, &pOldBackBuffer);
			m_pd3dDevice->GetDepthStencilSurface(&pOldZBuffer);
			m_pd3dDevice->GetViewport(&oldViewport);

			//-------------------------------------------------
			// ·»´õ¸µÅ¸°Ù º¯°æ
			//-------------------------------------------------
			m_pd3dDevice->SetRenderTarget(0, m_pColorMapSurf);
			m_pd3dDevice->SetRenderTarget(1, m_pDepthMapSurf);
			m_pd3dDevice->SetDepthStencilSurface(m_pMapZ);
			m_pd3dDevice->SetViewport(&viewport);

			// ·»´õ¸µÅ¸°Ù Å¬¸®¾î
			m_pd3dDevice->Clear(0L, NULL,
							D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
							0xffffff, 1.0f, 0L);

			//-------------------------------------------------
			// ¼ÎÀÌ´õ ¼³Á¤
			//-------------------------------------------------
			hTechnique = m_pEffect->GetTechniqueByName( "TShader" );
			m_pEffect->SetTechnique( hTechnique );
			m_pEffect->Begin( NULL, 0 );
			m_pEffect->Pass( 0 );
			
			//-------------------------------------------------
			// ¼ÎÀÌ´õ »ó¼ö ¼³Á¤
			//-------------------------------------------------
			// ÁÂÇ¥º¯È¯
			m = m_mWorld * m_mView * m_mProj;
			m_pEffect->SetMatrix( m_hmWVP, &m );

			// ±¤¿ø
			D3DXMatrixInverse( &m, NULL, &m_mWorld);
			D3DXVec4Transform( &v, &m_LightDir, &m );
			D3DXVec4Normalize( &v, &v );v.w = 0.3f;
			m_pEffect->SetVector( m_hvDir, &v );

			//-------------------------------------------------
			// ·»´õ
			//-------------------------------------------------
			D3DMATERIAL9 *pMtrl = m_pMeshBg->m_pMaterials;
			for( i=0; i<m_pMeshBg->m_dwNumMaterials; i++ ) {
				// ¸Þ½Ã»ö
				v.x = pMtrl->Diffuse.r;
				v.y = pMtrl->Diffuse.g;
				v.z = pMtrl->Diffuse.b;
				v.w = pMtrl->Diffuse.a;
				m_pEffect->SetVector( m_hvCol, &v );
				// ÅØ½ºÃ³
				m_pEffect->SetTexture("DecaleMap"
								, m_pMeshBg->m_pTextures[i]);

				m_pMeshBg->m_pLocalMesh->DrawSubset( i ); // •`‰æ
				pMtrl++;
			}

			m_pEffect->End();

			//-------------------------------------------------
			//-------------------------------------------------
			// ÆÐ½º2,3:Æ÷±×¸Ê »ý¼º
			//-------------------------------------------------
			//-------------------------------------------------

			//-------------------------------------------------
			// ·»´õ¸µÅ¸°Ù º¯°æ
			//-------------------------------------------------
			m_pd3dDevice->SetRenderTarget(0, m_pFogMapSurf);
			m_pd3dDevice->SetRenderTarget(1, NULL);
			m_pd3dDevice->SetViewport(&viewport);
			// ·»´õ¸µÅ¸°Ù Å¬¸®¾î
			m_pd3dDevice->Clear(0L, NULL,
							D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
							0x0, 1.0f, 0L);

			//-------------------------------------------------
			// ¼ÎÀÌ´õ ¼³Á¤
			//-------------------------------------------------
			hTechnique = m_pEffect->GetTechniqueByName( "TVolume" );
			m_pEffect->SetTechnique( hTechnique );
			m_pEffect->SetTexture("DepthMap", m_pDepthMap);
			m_pEffect->SetTexture("FrameBuffer", m_pFogMap);

			D3DXMatrixTranslation ( &mL, 0,1.0f,0 );
			m = mL*m_mWorld * m_mView * m_mProj;
			m_pEffect->SetMatrix( m_hmWVP, &m );

			mWT = m * mT;
			m_pEffect->SetMatrix( m_hmWVPT, &mWT );
			
			for( i=0 ; i<2 ; i++ ){
				for( DWORD j=0; j<m_pMesh->m_dwNumMaterials; j++ ){
					// ˆê“x•`‰æ‚ðI‚í‚ç‚¹‚ÄÄƒXƒ^[ƒg
					m_pd3dDevice->EndScene();
					m_pd3dDevice->BeginScene();
					m_pEffect->Begin( NULL, 0 );
					m_pEffect->Pass( i );

					m_pMesh->m_pLocalMesh->DrawSubset( j );
					m_pEffect->End();
				}
			}

			//-------------------------------------------------
			//-------------------------------------------------
			// 4ÆÐ½º:Àå¸é·»´õ
			//-------------------------------------------------
			//-------------------------------------------------

			//-------------------------------------------------
			// ·»´õ¸µÅ¸°Ù º¹±¸
			//-------------------------------------------------
			m_pd3dDevice->SetRenderTarget(0, pOldBackBuffer);
			m_pd3dDevice->SetDepthStencilSurface(pOldZBuffer);
			m_pd3dDevice->SetViewport(&oldViewport);
			pOldBackBuffer->Release();
			pOldZBuffer->Release();

			//-------------------------------------------------
			// ¼ÎÀÌ´õ ¼³Á¤
			//-------------------------------------------------
			hTechnique = m_pEffect->GetTechniqueByName( "TFinal" );
			m_pEffect->SetTechnique( hTechnique );
			m_pEffect->Begin( NULL, 0 );
			m_pEffect->Pass( 0 );
			m_pEffect->SetTexture( "FogMap",   m_pFogMap );
			m_pEffect->SetTexture( "ColorMap", m_pColorMap );

			// ¹öÆÛÅ¬¸®¾î
			m_pd3dDevice->Clear( 0L, NULL,
							D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
							0x00404080, 1.0f, 0L );

			m_pd3dDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_TEX1 );
			typedef struct {FLOAT p[4]; FLOAT tu, tv;} TVERTEX;
			TVERTEX Vertex[4] = {
				//         x               y     z rhw tu  tv
				{             0,              0, 0, 1, ds, dt},
				{(FLOAT)m_Width,              0, 0, 1,  s, dt},
				{(FLOAT)m_Width,(FLOAT)m_Height, 0, 1,  s,  t},
				{             0,(FLOAT)m_Height, 0, 1, ds,  t},
			};
			m_pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN
							, 2, Vertex, sizeof( TVERTEX ) );

			m_pEffect->End();
		}

#if 0 // µð¹ö±×¿ë ÅØ½ºÃ³ Ãâ·Â
	m_pd3dDevice->SetTextureStageState(0,D3DTSS_COLOROP,    D3DTOP_SELECTARG1);
	m_pd3dDevice->SetTextureStageState(0,D3DTSS_COLORARG1,  D3DTA_TEXTURE);
	m_pd3dDevice->SetTextureStageState(1,D3DTSS_COLOROP,    D3DTOP_DISABLE);
	m_pd3dDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_TEX1 );
	m_pd3dDevice->SetVertexShader(NULL);
	m_pd3dDevice->SetPixelShader(0);
	for(DWORD loop = 0; loop < 3; loop++){
		const float scale = 128.0f;
		typedef struct {FLOAT p[4]; FLOAT tu, tv;} TVERTEX;

		TVERTEX Vertex[4] = {
			//       x        y   z rhw tu tv
			{(loop  )*scale,    0,0, 1, ds, dt,},
			{(loop+1)*scale,    0,0, 1,  s, dt,},
			{(loop+1)*scale,scale,0, 1,  s,  t,},
			{(loop  )*scale,scale,0, 1, ds,  t,},
		};
		switch(loop){
		case 0: m_pd3dDevice->SetTexture( 0, m_pColorMap ); break;
		case 1: m_pd3dDevice->SetTexture( 0, m_pDepthMap ); break;
		case 2: m_pd3dDevice->SetTexture( 0, m_pFogMap   ); break;
		}
		m_pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, Vertex, sizeof( TVERTEX ) );
	}
#endif      
		RenderText();				// µµ¿ò¸» Ãâ·Â

        m_pd3dDevice->EndScene();	// ·»´õÁ¾·á
    }

    return S_OK;
}




//-------------------------------------------------------------
// Name: RenderText()
// Desc: »óÅÂ¿Í µµ¿ò¸»À» È­¸é¿¡ Ãâ·Â
//-------------------------------------------------------------
HRESULT CMyD3DApplication::RenderText()
{
    D3DCOLOR fontColor        = D3DCOLOR_ARGB(255,255,255,0);
    TCHAR szMsg[MAX_PATH] = TEXT("");

    FLOAT fNextLine = 40.0f; 

    // Á¶ÀÛ¹ý & ÀÎ¼ö Ãâ·Â
    fNextLine = (FLOAT) m_d3dsdBackBuffer.Height; 
	sprintf( szMsg, "Zoom: %f", m_zoom );
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
    lstrcpy( szMsg, TEXT("Use arrow keys to rotate object") );
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
    lstrcpy( szMsg, TEXT("Press 'z' or 'x' to change zoom") );
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
    // µð½ºÇÃ·¹ÀÌ »óÅÂ Ãâ·Â
    lstrcpy( szMsg, m_strFrameStats );
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
    lstrcpy( szMsg, m_strDeviceStats );
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
    
	return S_OK;
}




//-------------------------------------------------------------
// Name: MsgProc()
// Desc: WndProc ¿À¹ö¶óÀÌµù
//-------------------------------------------------------------
LRESULT CMyD3DApplication::MsgProc( HWND hWnd,
					UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_PAINT:
        {
            if( m_bLoadingApp )
            {
                // ·ÎµùÁß
                HDC hDC = GetDC( hWnd );
                TCHAR strMsg[MAX_PATH];
                wsprintf(strMsg, TEXT("Loading... Please wait"));
                RECT rct;
                GetClientRect( hWnd, &rct );
                DrawText( hDC, strMsg, -1, &rct,
						DT_CENTER|DT_VCENTER|DT_SINGLELINE );
                ReleaseDC( hWnd, hDC );
            }
            break;
        }

    }

    return CD3DApplication::MsgProc( hWnd, msg, wParam, lParam );
}




//-------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc: RestoreDeviceObjects() ¿¡¼­ »ý¼ºÇÑ ¿ÀºêÁ§Æ® ÇØÁ¦
//-------------------------------------------------------------
HRESULT CMyD3DApplication::InvalidateDeviceObjects()
{
	// ·»´õ¸µÅ¸°Ù
	SAFE_RELEASE(m_pFogMapSurf);
	SAFE_RELEASE(m_pFogMap);
	SAFE_RELEASE(m_pDepthMapSurf);
	SAFE_RELEASE(m_pDepthMap);
	SAFE_RELEASE(m_pColorMapSurf);
	SAFE_RELEASE(m_pColorMap);
	SAFE_RELEASE(m_pMapZ);

	m_pMesh  ->InvalidateDeviceObjects();				// ¸Þ½Ã
	m_pMeshBg->InvalidateDeviceObjects();				// ¸Þ½Ã
    if(m_pEffect!=NULL) m_pEffect->OnLostDevice();	// ¼ÎÀÌ´õ

    m_pFont->InvalidateDeviceObjects();	// ÆùÆ®

    return S_OK;
}




//-------------------------------------------------------------
// Name: DeleteDeviceObjects()
// Desc: InitDeviceObjects() ¿¡¼­ »ý¼ºÇÑ ¿ÀºêÁ§Æ® ÇØÁ¦
//-------------------------------------------------------------
HRESULT CMyD3DApplication::DeleteDeviceObjects()
{
	m_pMesh  ->Destroy();				// ¸Þ½Ã
	m_pMeshBg->Destroy();				// ¸Þ½Ã
	SAFE_RELEASE( m_pEffect );		// ¼ÎÀÌ´õ
	SAFE_RELEASE( m_pDecl );		// Á¤Á¡¼±¾ð

    m_pFont->DeleteDeviceObjects();	// ÆùÆ®

	return S_OK;
}




//-------------------------------------------------------------
// Name: FinalCleanup()
// Desc: Á¾·áÁ÷Àü¿¡ È£ÃâµÊ
//-------------------------------------------------------------
HRESULT CMyD3DApplication::FinalCleanup()
{
    SAFE_DELETE( m_pMesh   );	// ¸Þ½Ã
    SAFE_DELETE( m_pMeshBg );	// ¸Þ½Ã

    SAFE_DELETE( m_pFont );	// ÆùÆ®

    return S_OK;
}




