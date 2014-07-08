class ToonOutline
{
public:
	ToonOutline()
		: m_pEffect( NULL ), m_hmatWVP( NULL ), m_hTechnique( NULL )
	{
		_is_enable = true;
	}
	~ToonOutline()
	{
		if(m_pEffect)
			m_pEffect->Release();
	}

public:
	bool isEnable() const { return _is_enable;}
	void setEnable(bool new_enable) { _is_enable = new_enable;}

	bool Initialize(LPDIRECT3DDEVICE9 pd3dDevice, const char* pszEffectFile)
	{
		m_pd3dDevice = pd3dDevice;


		LPD3DXBUFFER pErr;
		if( FAILED( D3DXCreateEffectFromFileA( m_pd3dDevice, pszEffectFile, NULL, NULL, 
			NULL , NULL, &m_pEffect, &pErr )))
		{
			MessageBoxA( NULL, (LPCSTR)pErr->GetBufferPointer(), "ERROR", MB_OK);
			return false;
		}
		if(pErr)
			pErr->Release();

		if( NULL == m_pEffect )
			return false;

		m_hTechnique = m_pEffect->GetTechniqueByName( "TOutline" );
		m_hmatWVP = m_pEffect->GetParameterByName( NULL, "matWVP" );
		m_hLineColor = m_pEffect->GetParameterByName( NULL, "LineColor" );
		m_hLineScale = m_pEffect->GetParameterByName( NULL, "fLineScale" );

		if( NULL == m_hTechnique || NULL == m_hmatWVP || NULL == m_hLineColor || NULL == m_hLineScale )
			return false;

		D3DXVECTOR4 vColor( 0.0f, 0.0f, 0.0f, 0.0f );
		SetLineColor( &vColor );

		float fScale = 0.5f;
		SetLineScale( fScale );

		return true;
	}
	bool RenderStart(Camera& camera)
	{
		if( ! isEnable()) return false;
		if( ! &camera.getBinded())
			return false;
		LPDIRECT3DDEVICE9 device = camera.getBinded().getDevice();
		D3DXMATRIX world, VP = camera.createViewMatrix() * camera.createProjectionMatrix();
		device->GetTransform(D3DTS_WORLD, &world);
		
		D3DXMATRIX matWVP = world * VP;
		m_pEffect->SetMatrix( m_hmatWVP, &matWVP );

		if( FAILED( m_pEffect->SetTechnique( m_hTechnique ) ) )
			return false;


		static LPDIRECT3DVERTEXDECLARATION9 _decl = 0;
		if( ! _decl)
		{
			D3DVERTEXELEMENT9 elem[] = {
				{0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
				{0, 16, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
				D3DDECL_END()
			};
			device->CreateVertexDeclaration(elem, &_decl);
		}

		device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
		device->SetVertexDeclaration(_decl);

		m_pEffect->Begin( NULL, 0 );
		m_pEffect->BeginPass( 0 );

		return true;
	}
	void RenderEnd(Camera& camera)
	{
		m_pEffect->EndPass();
		m_pEffect->End();

		if( ! &camera.getBinded())
			return;
		LPDIRECT3DDEVICE9 device = camera.getBinded().getDevice();
		device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);
		device->SetVertexDeclaration(0);
	}

	void SetLineColor( D3DXVECTOR4 *pColor )
	{
		if( m_pEffect )
		{
			m_pEffect->SetVector( m_hLineColor, pColor );
		}
	}
	void SetLineScale( float fScale )
	{
		if( m_pEffect )
		{
			m_pEffect->SetFloat( m_hLineScale, fScale );
		}
	}

private:

	LPD3DXEFFECT		m_pEffect;
	D3DXHANDLE			m_hTechnique;
	D3DXHANDLE			m_hmatWVP;
	D3DXHANDLE			m_hLineColor;
	D3DXHANDLE			m_hLineScale;
	LPDIRECT3DDEVICE9	m_pd3dDevice;
	bool _is_enable;
};