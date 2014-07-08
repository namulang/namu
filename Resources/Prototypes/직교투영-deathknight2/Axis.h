#pragma once
#include <d3dx9.h>

#define D3DFVF_AXISVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)
struct AXISVERTEX
{
	FLOAT x, y, z;      // The untransformed, 3D position for the vertex
	DWORD color;        // The vertex color
};

class CAxis
{
private:
	LPDIRECT3DDEVICE9				m_Device;
	LPDIRECT3DVERTEXBUFFER9	m_AxisVB;
public:
	HRESULT Setup(LPDIRECT3DDEVICE9 Device);
	void Render(void);
	CAxis(void);
	virtual ~CAxis(void);
};
