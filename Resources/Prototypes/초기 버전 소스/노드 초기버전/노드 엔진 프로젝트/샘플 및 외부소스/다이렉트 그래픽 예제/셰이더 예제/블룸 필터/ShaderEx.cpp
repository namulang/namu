// Implementation of the CShaderEx class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CShaderEx::CShaderEx()
{
	m_pDev	= NULL;
	m_pEft	= NULL;
	
	m_pTex	= NULL;
}


CShaderEx::~CShaderEx()
{
	Destroy();
}


INT CShaderEx::Create(PDEV pDev)
{
	HWND	hWnd;
	HRESULT	hr=0;

	m_pDev	= pDev;

	////////////////////////////////////////////////////////////////////////////
	// Base Code
	D3DDEVICE_CREATION_PARAMETERS ppm;
	m_pDev->GetCreationParameters(&ppm);

	hWnd = ppm.hFocusWindow;


	DWORD dwFlags = 0;
	LPD3DXBUFFER	pErr	= NULL;

	#if defined( _DEBUG ) || defined( DEBUG )
		dwFlags |= D3DXSHADER_DEBUG;
	#endif


	// 쉐이더 코드 컴파일
	hr = D3DXCreateEffectFromFile(	m_pDev
									,	"data/Shader.fx"
									,	NULL
									,	NULL
									,	dwFlags
									,	0
									,	&m_pEft
									,	&pErr);
		
	if ( FAILED(hr) )
	{
		if(pErr)
		{
			MessageBox( hWnd, (char*)pErr->GetBufferPointer(), "Err", 0);
			pErr->Release();	pErr = NULL;
		}

		return -1;
	}

	// 정점 전언자
	D3DVERTEXELEMENT9 vertex_decl[MAX_FVF_DECL_SIZE]={0};
	D3DXDeclaratorFromFVF(VtxDUV1::FVF, vertex_decl);
	
	if( FAILED( hr = m_pDev->CreateVertexDeclaration(vertex_decl, &m_pFVF)))
		return -1;

	//
	////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////
	// 쉐이더 테스트용 Data
	// 테스트용 이미지
	D3DXCreateTextureFromFile(m_pDev, "Texture/Earth.bmp", &m_pTex);
	D3DXCreateTextureFromFileEx(m_pDev, "Texture/pattern_circle.png", D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT
		, D3DX_DEFAULT, 0x00FFFFFF, NULL, NULL, &texture1);


	//	버텍스 버퍼 생성
	m_pDev->CreateVertexBuffer(	4 * sizeof(MYVERTEX), 0, DEFAULT_CENGINE_D3DFVF_MYVERTEX, D3DPOOL_DEFAULT, &vertexbuffer, NULL);
	//	버텍스 초기화:		
	m_pDev->SetFVF(DEFAULT_CENGINE_D3DFVF_MYVERTEX);
	m_pDev->SetStreamSource(0, vertexbuffer, 0, sizeof(MYVERTEX));


	setVertex(-600, -450, 600, 450);
	return 0;
}
void	CShaderEx::setVertex(float x1, float y1, float x2, float y2, float u1, float v1, float u2, float v2, DWORD color)
{	
	//	버퍼 잠구기:
	vertexbuffer->Lock(0, 4 * sizeof(MYVERTEX), (void**) &vertex, NULL);	
	//	버텍스 설정:
	//		좌하:
	vertex[0].x = x1;	vertex[0].y = y2;
	vertex[0].tu = u1;	vertex[0].tv = v1;
	vertex[0].z = 1.0f;	vertex[0].color = color;
	//		좌상:
	vertex[1].x = x1;	vertex[1].y = y1;
	vertex[1].tu = u1;	vertex[1].tv = v2;
	vertex[1].z = 1.0f;	vertex[1].color = color;
	//		우하:
	vertex[2].x =x2;	vertex[2].y = y2;
	vertex[2].tu = u2;	vertex[2].tv =v1;
	vertex[2].z = 1.0f;	vertex[2].color = color;
	//		우상:
	vertex[3].x = x2;	vertex[3].y = y1;
	vertex[3].tu = u2;	vertex[3].tv = v2;
	vertex[3].z = 1.0f;	vertex[3].color = color;
	//	버퍼 풀기:
	vertexbuffer->Unlock();

}
void CShaderEx::Destroy()
{
	SAFE_RELEASE(	m_pFVF	);
	SAFE_RELEASE(	m_pEft	);
	SAFE_RELEASE(	vertexbuffer );
	SAFE_RELEASE( texture1);
}


INT CShaderEx::Restore()
{
	return m_pEft->OnResetDevice();
}

void CShaderEx::Invalidate()
{
	m_pEft->OnLostDevice();
}


INT CShaderEx::FrameMove()
{
	return 0;
}


void CShaderEx::Render()
{
	static D3DXMATRIX mtI(1,0,0,0,    0,1,0,0,    0,0,1,0,    0,0,0,1);
	HRESULT	hr = 0;

	// 변환 행렬을 초기화
	////////////////////////////////////////////////////////////////////////////
	// for Test
	D3DXMATRIXA16	viewer_matrix,
					projection_matrix;
	D3DXMatrixIdentity(&viewer_matrix);		
	D3DXMatrixIdentity(&projection_matrix);
	//	초기화:
	D3DXMATRIXA16	translation_matrix,
					rotation_matrix,
					scaling_matrix;
	//	행렬 구하기:
	D3DXMatrixTranslation(&translation_matrix, 0.0f, 0.0f, 0.0f); // 평행이동	
	D3DXMatrixRotationZ(&rotation_matrix, 0.0f );// 회전	
	D3DXMatrixScaling(&scaling_matrix, 1.0f, 1.0f, 1.0f);// 크기조절
	//	구한 행렬을 적용하여 변환:
	m_pDev->SetTransform(D3DTS_WORLD, &(translation_matrix * rotation_matrix * scaling_matrix));
	m_pDev->SetTransform(D3DTS_VIEW, &viewer_matrix);	
	D3DXMATRIXA16	texture_correction_matrix;
	D3DXMatrixTranslation(&texture_correction_matrix,-0.5f,-0.5f,0);
	//	투영 행렬:
	D3DXMatrixOrthoLH(	&projection_matrix, 1200.0f, 900.0f, 1.0f, 0.0f );		
	m_pDev->SetTransform(D3DTS_PROJECTION, &(texture_correction_matrix * projection_matrix));		

	
	
	m_pDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDev->SetRenderState(D3DRS_FOGENABLE, FALSE);
	m_pDev->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE);
	//m_pDev->SetRenderState( D3DRS_ALPHATESTENABLE , FALSE);
	m_pDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pDev->SetRenderState(D3DRS_DITHERENABLE, FALSE);
	m_pDev->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
	m_pDev->SetRenderState(D3DRS_ZENABLE, FALSE);
	m_pDev->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
	m_pDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); // COLOR인수(ARG)1과 2의 값을 곱한것을 최종색으로 렌더링함
	m_pDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE); // 인수(ARG)1은 텍스쳐의 색
	m_pDev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE); // 인수2는 버텍스의 색		
	//m_pDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//m_pDev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	//m_pDev->SetTextureStageState(0, D3DTSS_COLOROP  , D3DTOP_MODULATE);

	//m_pDev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	//m_pDev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	//m_pDev->SetSamplerState(0, D3DSAMP_ADDRESSW, D3DTADDRESS_CLAMP);
	/*
	for(int i=0; i<8; ++i)
	{
		m_pDev->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		m_pDev->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		m_pDev->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}
	//
	////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////
	// 쉐이더 적용*/
	static float	width = 1600.0f;
	static float	height = 1200.0f;
	static float	delta = 0.5f;
	LPDIRECT3DTEXTURE9	TEXTURE;
	LPDIRECT3DTEXTURE9	XTEXTURE;
	LPDIRECT3DTEXTURE9	YTEXTURE;
	
	LPDIRECT3DSURFACE9	SURFACE;
	LPDIRECT3DSURFACE9	XSURFACE;
	LPDIRECT3DSURFACE9	YSURFACE;

	LPDIRECT3DSURFACE9	OLDBUFFER;
	m_pDev->CreateTexture( 320, 240, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &TEXTURE, NULL);
	TEXTURE->GetSurfaceLevel(0, &SURFACE);
	m_pDev->CreateTexture( 320, 240, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &XTEXTURE, NULL);
	XTEXTURE->GetSurfaceLevel(0, &XSURFACE);
	m_pDev->CreateTexture( 320, 240, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &YTEXTURE, NULL);
	YTEXTURE->GetSurfaceLevel(0, &YSURFACE);
	
	m_pDev->GetRenderTarget(0, &OLDBUFFER);
	m_pDev->SetRenderTarget(0, SURFACE);
	m_pDev->BeginScene();
	m_pDev->SetTexture(0, m_pTex);
	setVertex(-600, -450, 600, 450);
	m_pDev->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2);	
	m_pDev->EndScene();
	//	TEXTURE : 렌더링한 장면이 들어있는 소스.
	//////////////////////////////////////////////////////////////////////////
	m_pDev->SetRenderTarget(0, YSURFACE); // 원본을 y에 찍음
	
	setVertex(-1, -1, 1, 1);

	m_pEft->Begin(0, 0);
	m_pEft->SetTechnique("Tech");			
	m_pEft->BeginPass(0);

	m_pEft->SetTexture("m_TxDif", TEXTURE); // 원본
	m_pDev->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2);	

	m_pEft->EndPass();
	//hr = m_pEft->SetFloat("m_TexW", width);
	//hr = m_pEft->SetFloat("m_TexH", height);	
	//////////////////////////////////////////////////////////////////////////
	for (int n=0; n< 1 ;n++)
	{
		m_pDev->SetRenderTarget(0, XSURFACE); // Y를 X에 찍음

		m_pEft->BeginPass(1);
		m_pEft->SetTexture("m_TxDif", YTEXTURE); // 원본
		m_pDev->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2);	
		m_pEft->EndPass();
		////////////////////////////////////////////kkkkkk//////////////////////////////
		m_pDev->SetRenderTarget(0, YSURFACE);

		m_pEft->BeginPass(2);
		m_pEft->SetTexture("m_TxDif", XTEXTURE); // X한걸 Y에 찍음	
		m_pDev->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2);	
		m_pEft->EndPass();
	}
	//////////////////////////////////////////////////////////////////////////
	m_pDev->SetRenderTarget(0, OLDBUFFER);
	OLDBUFFER->Release();

	m_pEft->BeginPass(3);	
	//setVertex(-600, -450, 600, 450);
	m_pEft->SetTexture("m_TxDif", TEXTURE); // 원본
	m_pEft->SetTexture("m_TxDiB", YTEXTURE); // 블러한거
	m_pEft->SetFloat("_bloom", 0.5f);
	m_pDev->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2);	
	m_pEft->EndPass();
	m_pEft->End();

	//	RESTORE
	
	TEXTURE->Release();
	SURFACE->Release();
	XTEXTURE->Release();
	XSURFACE->Release();
	YTEXTURE->Release();
	YSURFACE->Release();

}


