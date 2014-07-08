//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia 07 - 10 - 10 게임 이미지 로딩과 랜더에 관한 클래스
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "defines.h"

class CDXImage
{
private:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;						// 버텍스버퍼
	LPDIRECT3DTEXTURE9*				m_pTexture;				// 텍스쳐 버퍼
	LPDIRECT3DINDEXBUFFER9			m_pIB;						// 인덱스 버퍼
	DWORD									m_FVF;						// FVF
	DWORD									m_dwVertexNum;			// 버텍스버퍼 갯수
	DWORD									m_dwIndexNum;			// 인덱스버퍼 갯수
	DWORD									m_dwTriangleNumber;	// 인덱스버퍼없을때의 삼각형 갯수
	BOOL										m_bIndex;					// 인덱스 버퍼를 설정할것인가의 여부
	BOOL										m_bTexture;				// 텍스쳐 버퍼를 설정할것인가의 여부
	DWORD									m_dwTextureNum;
	DWORD									m_dwTime;
	DWORD									m_dwNowTime;
	int											m_nCount;
public:
	BOOL	Setting(BOOL Index, BOOL Texture, DWORD dwTextureNum = 0); // 초기 설정
	BOOL VertexBufferSetUp(LPDIRECT3DDEVICE9 pDevice, int nVertices, CUSTOMVERTEX* pVertices); // 버텍스 버퍼 셋업
	BOOL NoneTextureVertexBufferSetUp(LPDIRECT3DDEVICE9 pDevice, int nVertices, NONETEXTUREVERTEX* pVertices); // NONE 버텍스 버퍼 셋업
	BOOL IndexBufferSetUp(LPDIRECT3DDEVICE9 pDevice, int nIndices, tagIndex* pIndices); // 인덱스 버퍼 셋업
	BOOL TextureSetUp(LPDIRECT3DDEVICE9 pDevice, char* szFileName, DWORD dwTextureNum); // 텍스쳐 버퍼 셋업
	void	Render(LPDIRECT3DDEVICE9 pDevice, DWORD dwTextureNum = 0); // 랜더
	void	RenderCoolTime(LPDIRECT3DDEVICE9 pDevice); // 쿨타임
	CDXImage(void);
public:
	virtual ~CDXImage(void);
};
