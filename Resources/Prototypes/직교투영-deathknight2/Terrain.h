//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 10 지형 클래스
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "defines.h"
#include "DXImage.h"

#define MAPSIZEX 128
#define MAPSIZEZ 128

class CTerrain
{
private:
	LPDIRECT3DDEVICE9	m_pDevice;				// 장치 드라이버
	int							m_nTriangle;			// 삼각형의 갯수
	D3DXVECTOR3*		m_vHeightMap;		//하이트맵의 정점을 저장할곳
	CDXImage				m_Terrain;				// 지형이미지
public:
	BOOL SetUp(LPDIRECT3DDEVICE9 pDevice); // 셋업
	CTerrain(void);
	virtual ~CTerrain(void);
};
