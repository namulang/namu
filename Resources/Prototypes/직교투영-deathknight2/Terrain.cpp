#include ".\terrain.h"

CTerrain::CTerrain(void)
{
}

CTerrain::~CTerrain(void)
{
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 10 지형 셋
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
BOOL CTerrain::SetUp(LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;

	//삼각형의 갯수
	m_nTriangle = (MAPSIZEX - 1) * (MAPSIZEZ - 1) * 2;

	///하이트맵의 정점을 보관할 배열을 동적할당한다
	m_vHeightMap = new D3DXVECTOR3[MAPSIZEX * MAPSIZEZ];
	// 지형 셋팅
	m_Terrain.Setting(TRUE, TRUE);
	return TRUE;
}
