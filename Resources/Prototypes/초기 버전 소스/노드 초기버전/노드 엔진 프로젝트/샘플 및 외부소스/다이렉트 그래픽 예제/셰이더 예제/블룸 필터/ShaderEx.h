// Interface for the CShaderEx class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _ShaderEx_H_
#define _ShaderEx_H_

typedef D3DXVECTOR2							VEC2;
typedef	D3DXVECTOR3							VEC3;
typedef D3DXVECTOR4							VEC4;
typedef D3DXMATRIX							MATA;

typedef LPDIRECT3DDEVICE9					PDEV;

typedef	LPD3DXEFFECT						PDEF;
typedef LPDIRECT3DVERTEXDECLARATION9		PDVD;
typedef LPDIRECT3DTEXTURE9					PDTX;

typedef struct myvertex
{
	FLOAT x, y, z;
	DWORD color; // RGBA
	FLOAT tu, tv; // 텍스쳐 1개 사용
} MYVERTEX;
#define DEFAULT_CENGINE_D3DFVF_MYVERTEX		(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
class CShaderEx
{
public:
	struct VtxDUV1
	{
		VEC3	p;
		DWORD	d;
		FLOAT	u,v;
		
		VtxDUV1()								  : p(0,0,0), d(0xFFFFFFFF){}
		VtxDUV1(  FLOAT X, FLOAT Y, FLOAT Z
			,  FLOAT U, FLOAT V, DWORD D=0XFFFFFFFF) : p(X,Y,Z), u(U), v(V), d(D){}

		enum {FVF = (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1),};
	};

public:
	PDEV		m_pDev;				// Device

	PDVD		m_pFVF;				// Vertex Declaration
	PDEF		m_pEft;				// Effect
	MYVERTEX*	vertex;			// Vertex Buffer
	LPDIRECT3DVERTEXBUFFER9 vertexbuffer;
	PDTX		m_pTex;				// Texture
	LPDIRECT3DTEXTURE9	texture1;
	
	
public:
	CShaderEx();
	virtual ~CShaderEx();
	
	INT		Create(PDEV pDev);
	void	Destroy();

	INT		FrameMove();
	void	Render();

	INT		Restore();
	void	Invalidate();
	void	setVertex(float x1, float y1, float x2, float y2, 
		float u1 = 0.0f, float v1 = 0.0f, float u2 = 1.0f, float v2 = 1.0f,
		DWORD color = D3DCOLOR_ARGB(255,255,255,255));
};

#endif
