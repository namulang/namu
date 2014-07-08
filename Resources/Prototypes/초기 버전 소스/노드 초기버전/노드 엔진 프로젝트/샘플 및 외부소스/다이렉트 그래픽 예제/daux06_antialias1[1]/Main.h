// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef _Main_H_
#define _Main_H_



struct VtxD
{
    D3DXVECTOR3	p;
    DWORD		d;

	VtxD() : p(0,0,0), d(0xFFFFFFFF)	{}
	VtxD(FLOAT X, FLOAT Y, FLOAT Z, DWORD D=0xFFFFFFFF): p(X,Y,Z), d(D){}
	VtxD(const D3DXVECTOR3& _p, DWORD D=0xFFFFFFFF) : p(_p), d(D){}

	enum { FVF = (D3DFVF_XYZ|D3DFVF_DIFFUSE),};
};



class CMain : public CD3DApp
{
protected:
	ID3DXFont*		m_pD3DXFont;            // D3DX font

	VtxD			m_pVtx[4];



public:
	CMain();

	virtual INT		Init();
	virtual void	Destroy();

	virtual INT		FrameMove();
	virtual void	Render();

	virtual LRESULT MsgProc( HWND, UINT, WPARAM, LPARAM);
};

extern CMain*	g_pApp;

#endif
