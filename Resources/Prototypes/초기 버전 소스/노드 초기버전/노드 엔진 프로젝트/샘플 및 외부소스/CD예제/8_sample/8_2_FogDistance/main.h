//-------------------------------------------------------------
// File: main.h
//
// Desc: 거리포그
//-------------------------------------------------------------
#pragma once




//-------------------------------------------------------------
// 정의 & 상수
//-------------------------------------------------------------
// 입력데이터를 보존할 구조체
struct UserInput
{
    BOOL bRotateUp;
    BOOL bRotateDown;
    BOOL bRotateLeft;
    BOOL bRotateRight;
    BOOL bZ;
    BOOL bX;
    BOOL bA;
    BOOL bS;
};




//-------------------------------------------------------------
// Name: class CMyD3DApplication
// Desc: 어플리케이션 클래스
//-------------------------------------------------------------
class CMyD3DApplication : public CD3DApplication
{
	CD3DMesh						*m_pMesh;	// 모델
	LPDIRECT3DVERTEXDECLARATION9	m_pDecl;	// 정점선언
	LPD3DXEFFECT					m_pEffect;	// 이펙트
	D3DXHANDLE						m_hmWVP;	// 월드~투영행렬
	D3DXHANDLE						m_hvCol;	// 메시색
	D3DXHANDLE						m_hvDir;	// 광원방향
	D3DXHANDLE						m_hvFog;	// 포그의 near/far
	D3DXHANDLE						m_hvEye;	// 시점 위치

	D3DXMATRIX						m_mWorld;	// 월드행렬
	D3DXMATRIX						m_mView;	// 뷰행렬
	D3DXMATRIX						m_mProj;	// 투영행렬
	D3DXVECTOR4						m_LightDir;	// 광원방향
	D3DXVECTOR3						m_Eye;		// 시점 위치

	FLOAT						m_near;			// 포그시작
	FLOAT						m_far;			// 포그종료
    FLOAT						m_fWorldRotX;	// X축회전
    FLOAT						m_fWorldRotY;	// Y축회전

	BOOL						m_bLoadingApp;	// 로드중?
    CD3DFont*					m_pFont;		// 폰트
    UserInput					m_UserInput;	// 입력데이터
	
protected:
    virtual HRESULT OneTimeSceneInit();
    virtual HRESULT InitDeviceObjects();
    virtual HRESULT RestoreDeviceObjects();
    virtual HRESULT InvalidateDeviceObjects();
    virtual HRESULT DeleteDeviceObjects();
    virtual HRESULT Render();
    virtual HRESULT FrameMove();
    virtual HRESULT FinalCleanup();
    virtual HRESULT ConfirmDevice(D3DCAPS9*, DWORD, D3DFORMAT);

    HRESULT RenderText();

    void    UpdateInput( UserInput* pUserInput );
public:
    LRESULT MsgProc( HWND hWnd, UINT msg
					, WPARAM wParam, LPARAM lParam );
    CMyD3DApplication();
    virtual ~CMyD3DApplication();
};
