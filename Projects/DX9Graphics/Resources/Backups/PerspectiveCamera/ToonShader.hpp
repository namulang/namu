class ToonShadow
{
public:
	ToonShadow()
		: m_pEffect( NULL ), m_hmatWVP( NULL ), m_hTechnique( NULL ), m_pShadowTexture( NULL )
	{
		_is_enable = true;
	}
	~ToonShadow()
	{
		if(m_pShadowTexture)
			m_pShadowTexture->Release();
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

		m_hTechnique = m_pEffect->GetTechniqueByName( "TShadow" );
		m_hmatWVP = m_pEffect->GetParameterByName( NULL, "matWVP" );
		m_hmatWV = m_pEffect->GetParameterByName( NULL, "matWV" );
		m_hLightDir = m_pEffect->GetParameterByName( NULL, "vLightDir" );

		if( NULL == m_hTechnique || NULL == m_hmatWVP)
			return false;

		if( FAILED( D3DXCreateTextureFromFileA( m_pd3dDevice, "./Shader/Shadow.bmp", &m_pShadowTexture ) ) ) 
			return FALSE;

		return true;
	}
	bool RenderStart(PerspectiveCamera& camera)
	{
		if( ! isEnable()) return false;
		if( ! &camera.getBinded())
			return false;
		LPDIRECT3DDEVICE9 device = camera.getBinded().getDevice();
		D3DXMATRIX world;
		device->GetTransform(D3DTS_WORLD, &world);

		D3DXMATRIX	matView = camera.createViewMatrix(),
					matWV	= world * matView,
					matWVP	= matWV * camera.createProjectionMatrix();

		PerspectiveCamera::Connector& connector = camera.getConnector();		
		m_light.x = connector.getLightX().getValue();
		m_light.y = connector.getLightY().getValue();
		m_light.z = connector.getLightZ().getValue();

		m_pEffect->SetMatrix(m_hmatWVP, &matWVP );		
		m_pEffect->SetMatrix( m_hmatWV, &matWV );
		m_pEffect->SetVector( m_hLightDir, (D3DXVECTOR4*)&m_light);

		if( FAILED( m_pEffect->SetTechnique( m_hTechnique ) ) )
			return false;	

		static LPDIRECT3DVERTEXDECLARATION9 _decl = 0;
		if( ! _decl)
		{
			D3DVERTEXELEMENT9 elem[] = {
				{0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
				{0, 16, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
				{0, 28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
				D3DDECL_END()
			};
			device->CreateVertexDeclaration(elem, &_decl);
		}

		device->SetVertexDeclaration(_decl);
		m_pEffect->Begin( NULL, 0 );
		m_pEffect->BeginPass( 0 );

		m_pd3dDevice->SetTextureStageState( 0 ,D3DTSS_COLOROP , D3DTOP_MODULATE ); 
		m_pd3dDevice->SetTextureStageState( 0 ,D3DTSS_COLORARG1, D3DTA_TEXTURE ); 
		m_pd3dDevice->SetTextureStageState( 0 ,D3DTSS_COLORARG2, D3DTA_DIFFUSE ); 
		m_pd3dDevice->SetTextureStageState( 1 ,D3DTSS_COLOROP, D3DTOP_MODULATE ); 
		m_pd3dDevice->SetTextureStageState( 1 ,D3DTSS_COLORARG1, D3DTA_CURRENT ); 
		m_pd3dDevice->SetTextureStageState( 1 ,D3DTSS_COLORARG2, D3DTA_TEXTURE ); 
		m_pd3dDevice->SetTexture( 1, m_pShadowTexture );

		return true;
	}
	void RenderEnd(PerspectiveCamera& camera)
	{
		if( ! &camera.getBinded())
			return;

		m_pEffect->EndPass();
		m_pEffect->End();
		
		camera.getBinded().getDevice()->SetVertexDeclaration(0);
		m_pd3dDevice->SetTexture( 1, NULL );
		m_pd3dDevice->SetTextureStageState( 0 , D3DTSS_COLORARG2 , D3DTA_CURRENT ); 
		m_pd3dDevice->SetTextureStageState( 1 , D3DTSS_COLOROP , D3DTOP_DISABLE ); 
	}

private:
	LPD3DXEFFECT		m_pEffect;
	D3DXHANDLE			m_hTechnique;
	D3DXHANDLE			m_hmatWVP;
	D3DXHANDLE			m_hmatWV;
	D3DXHANDLE			m_hLightDir;
	LPDIRECT3DDEVICE9	m_pd3dDevice;
	IDirect3DTexture9*	m_pShadowTexture;
	D3DXVECTOR4			m_light;
	bool _is_enable;
};