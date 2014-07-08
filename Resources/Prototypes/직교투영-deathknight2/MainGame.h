//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 10 게임에 필요한 모든 부분이 이곳에 모인다.
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "defines.h"
#include "DXImage.h"
#include "Camera.h"
#include "CInput.h"
#include "Terrain.h"
#include "Texture.h"
#include "Axis.h"

class CMainGame
{
private:
	CInputDevice				m_InputMouse;	// 마우스
	CInputDevice				m_InputKeyBoard;// 키보드
	CCamera						m_Camera;
	LPDIRECTINPUT8			m_pDI;				// 인풋장치
	CDXImage					m_Image[2];
	LPDIRECT3DDEVICE9	m_pDevice;				// 장치 드라이버
	CUSTOMVERTEX			m_Vertices[6];
	DWORD						m_dwTime;		
	DWORD						m_dwNowTime;
	CAxis							m_Axis;
	float							m_fAngle;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;						// 버텍스버퍼
	LPDIRECT3DINDEXBUFFER9			m_pIB;						// 인덱스 버퍼
	DWORD						m_dwColor;
private:
	void	CameraSetUp(void);						// 카메라 셋업
	BOOL InputSetUp(void);						// 인풋 셋업
	void	KeyBordMouseCameraUpdate(void);	// 키보드 마우스 카메라 업데이트
	void	Render(void);								// 그림 랜더
public:
	BOOL SetUp(LPDIRECT3DDEVICE9 Device); // 셋업 구문
	CMainGame(void);
	void Management(void); // PeekMessage 루프안에들어갈것
	virtual ~CMainGame(void);
};
