#include ".\axis.h"

CAxis::CAxis(void)
{
	
}

CAxis::~CAxis(void)
{
}
// 초기화
HRESULT CAxis::Setup(LPDIRECT3DDEVICE9 Device)
{
	m_Device = Device;
	AXISVERTEX	Vertex[] =
	{
		// X축
		{0.0f, 0.0f, 0.0f, 0xffff0000,},
		{10.0f, 0.0f, 0.0f, 0xffff0000,},
		// Y축
		{0.0f, 0.0f, 0.0f, 0xff00ff00,},
		{0.0f, 10.0f, 0.0f, 0xff00ff00,},
		// Z축
		{0.0f, 0.0f, 0.0f, 0xffff00ff,},
		{0.0f, 0.0f, 10.0f, 0xffff00ff,},
	};

	if( FAILED( m_Device->CreateVertexBuffer( 6*sizeof(AXISVERTEX), 	0, D3DFVF_AXISVERTEX, D3DPOOL_DEFAULT, &m_AxisVB, NULL ) ) )
	{
		return E_FAIL;
	}

	// Fill the vertex buffer.
	VOID* pVertices;
	if( FAILED( m_AxisVB->Lock( 0, sizeof(Vertex), (void**)&pVertices, 0 ) ) )
		return E_FAIL;
	memcpy( pVertices, Vertex, sizeof(Vertex) );
	m_AxisVB->Unlock();

	return S_OK;

}

void CAxis::Render(void)
{
	m_Device->SetTexture(0, NULL);
	m_Device->SetStreamSource( 0, m_AxisVB, 0, sizeof(AXISVERTEX) );
	m_Device->SetFVF( D3DFVF_AXISVERTEX );
	m_Device->DrawPrimitive( D3DPT_LINELIST, 0, 6 );
}
