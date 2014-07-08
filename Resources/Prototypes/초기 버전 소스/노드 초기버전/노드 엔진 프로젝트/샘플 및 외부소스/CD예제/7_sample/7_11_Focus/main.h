//-------------------------------------------------------------
// File: main.h
//
// Desc: 포커스 필터
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
    BOOL bZoomIn;
    BOOL bZoomOut;
};




//-------------------------------------------------------------
// Name: class CMyD3DApplication
// Desc: 어플리케이션 클래스
//-------------------------------------------------------------
class CMyD3DApplication : public CD3DApplication
{
	// 셰이더
	LPD3DXEFFECT		    m_pEffect;		// 이펙트
	D3DXHANDLE				m_hTechnique;	// 테크닉
	D3DXHANDLE				m_hafWeight;	// 가중치배열
	D3DXHANDLE				m_htSrcTex;		// 텍스처
	D3DXHANDLE				m_htBlurTex;	// 텍스처
	D3DXHANDLE				m_htBlendTex;	// 텍스처

	// 렌더링 타겟
	LPDIRECT3DSURFACE9		m_pMapZ;		// 깊이버퍼
	LPDIRECT3DTEXTURE9		m_pOriginalTex;	// 텍스처
	LPDIRECT3DSURFACE9		m_pOriginalSurf;// 표면
	LPDIRECT3DTEXTURE9		m_pPostTex[2];	// 텍스처
	LPDIRECT3DSURFACE9		m_pPostSurf[2];	// 표면

	// 메시
	CD3DMesh				*m_pMesh;
	CD3DMesh				*m_pMeshBg;
	LPDIRECT3DTEXTURE9		m_pTex;
			
	// 변환행렬
	D3DXMATRIX				m_mWorld;
	D3DXMATRIX				m_mView;
	D3DXMATRIX				m_mProj;

	BOOL					m_bLoadingApp;	// 로드중?
    CD3DFont*				m_pFont;		// 폰트
    UserInput				m_UserInput;	// 입력데이터

    FLOAT                   m_fWorldRotX;   // X축회전
    FLOAT                   m_fWorldRotY;   // Y축회전
    FLOAT                   m_fViewZoom;    // 시점거리

protected:
    virtual HRESULT OneTimeSceneInit();
    virtual HRESULT InitDeviceObjects();
    virtual HRESULT RestoreDeviceObjects();
    virtual HRESULT InvalidateDeviceObjects();
    virtual HRESULT DeleteDeviceObjects();
    virtual HRESULT Render();
    virtual HRESULT FrameMove();
    virtual HRESULT FinalCleanup();
    virtual HRESULT ConfirmDevice( D3DCAPS9*, DWORD, D3DFORMAT );

    HRESULT RenderText();

    void    UpdateInput( UserInput* pUserInput );
public:
    LRESULT MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
    CMyD3DApplication();
    virtual ~CMyD3DApplication();
};

