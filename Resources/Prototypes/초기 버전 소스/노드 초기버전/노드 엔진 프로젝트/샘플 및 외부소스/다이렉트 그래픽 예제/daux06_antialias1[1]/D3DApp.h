// Interface for the CD3DApp class.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef _D3DApp_H_
#define _D3DApp_H_


class CD3DApp
{
protected:
	HINSTANCE				m_hInst			;
	HWND					m_hWnd			;
	LPDIRECT3D9             m_pD3D			;									// D3D
	LPDIRECT3DDEVICE9       m_pd3dDevice	;									// Device
	D3DPRESENT_PARAMETERS	m_d3dpp			;

	DOUBLE					m_fFps;

public:
	CD3DApp();
	INT		Create( HINSTANCE hInst);
	INT		Run();

protected:
	INT		Render3D();
	void	Cleanup();
	void	UpdateStats();


protected:

	virtual INT		Init()		{	return 0;		}
	virtual void	Destroy()	{	return  ;		}

	virtual INT		FrameMove()	{	return 0;		}
	virtual void	Render()	{	return  ;		}

	virtual LRESULT MsgProc( HWND, UINT, WPARAM, LPARAM);

	
public:
	static LRESULT	WINAPI WndProc( HWND, UINT, WPARAM, LPARAM);
	static CD3DApp*	g_pD3DApp;
};


#endif
