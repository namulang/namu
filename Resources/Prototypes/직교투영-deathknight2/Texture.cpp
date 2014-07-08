#include ".\texture.h"

CTexture::CTexture(void)
{
	m_pTexture = NULL;
}

CTexture::~CTexture(void)
{
	SAFE_RELEASE(m_pTexture);
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 11 텍스쳐를 셋팅
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
BOOL CTexture::SetUp(LPDIRECT3DDEVICE9 pd3dDevice, char *szFileName)
{
	if(FAILED(D3DXCreateTextureFromFile(pd3dDevice, szFileName, &m_pTexture)))
	{
		MessageBox(g_hWnd, "텍스쳐 셋업 실패", "텍스쳐 클래스 에러", MB_OK);
		return FALSE;
	}
	return TRUE;
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  Narusia.07 - 10 - 11 텍스쳐 상태를 셋팅한다 
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CTexture::SetState(LPDIRECT3DDEVICE9 pd3dDevice)
{
	pd3dDevice->SetTexture( 0, m_pTexture );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, 0 );
	pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );	/// 0번 텍스처 스테이지의 확대 필터
	pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
}