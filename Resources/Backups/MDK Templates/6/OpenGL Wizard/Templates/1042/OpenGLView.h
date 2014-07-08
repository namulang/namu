// [!output PROJECT_NAME]View.h : iCOpenGLView 클래스의 인터페이스
//


#pragma once


class C[!output PROJECT_NAME]View : public CView
{
protected: // serialization에서만 만들어집니다.
	C[!output PROJECT_NAME]View();
	DECLARE_DYNCREATE(C[!output PROJECT_NAME]View)

// 특성
public:
	C[!output PROJECT_NAME]Doc* GetDocument() const;

	int height;
	int width;

	HDC hDC;
	HGLRC hRC;

	void InitOpenGL();
	void InitProjection();
	void InitShadingModel();
[!if SUPPORT_ALPHA_BLEND]
	void InitAlphaTest();
[!endif]
[!if SUPPORT_TEXTURE_EFFECT]
	void InitTexture();
[!endif]
[!if SUPPORT_OMNI_LIGHT || SUPPORT_SPOT_LIGHT]
	void InitLight();
[!endif]
[!if SUPPORT_FOG_EFFECT]
	void InitFog();
[!endif]
	void SetDCPixelFormat(HDC hDC);
	void DrawScene();

[!if SUPPORT_TEXTURE_EFFECT]
	void *LoadBMPfile(char *filename, BITMAPINFO **info);

	BITMAPINFO *info;
	void *bits;
[!endif]
[!if SUPPORT_SELECTION_EFFECT]
	GLuint select_buffer[20];
	GLuint Picking(CPoint point);
[!endif]

	float m_spinx;
	float m_spiny;
	bool m_lbutton;
	POINT m_prevpoint;
	GLUquadricObj *Obj;
	void OnChangeSize(int cx, int cy);


// 작업
public:

// 재정의
	public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현
public:
	virtual ~C[!output PROJECT_NAME]View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 메시지 맵 함수를 생성했습니다.
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
[!if SUPPORT_ANIMATION_EFFECT]	
	afx_msg void OnTimer(UINT nIDEvent);
[!endif]
		
};

#ifndef _DEBUG  // OpenGLView.cpp의 디버그 버전
inline C[!output PROJECT_NAME]Doc* C[!output PROJECT_NAME]View::GetDocument() const
   { return reinterpret_cast<C[!output PROJECT_NAME]Doc*>(m_pDocument); }
#endif

