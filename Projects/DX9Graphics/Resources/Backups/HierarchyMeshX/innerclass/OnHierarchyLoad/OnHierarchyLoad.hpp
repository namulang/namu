class OnHierarchyLoad : public ID3DXAllocateHierarchy
{
public:

	STDMETHOD( CreateFrame )( THIS_ LPCSTR Name, LPD3DXFRAME *pNewFrame )
	{
		HRESULT hr = S_OK;
		
		*pNewFrame = NULL;

		BoneFrame boneframe;
		AllocateName(Name, &boneframe.Name );

		D3DXMatrixIdentity( &boneframe.TransformationMatrix );
		D3DXMatrixIdentity( &boneframe.CombinedTransformMatrix );

		_owner.getFrameList().push(boneframe);

		*pNewFrame = ( D3DXFRAME *) & _owner.getFrameList()[_owner.getFrameList().getLengthLastIndex()];

		return S_OK;
	}
	STDMETHOD( CreateMeshContainer )( THIS_ LPCSTR Name, CONST D3DXMESHDATA *pMeshData, CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances, DWORD NumMaterials,	CONST DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer )
	{
		BoneMesh* boneMesh = new BoneMesh;
		memset( boneMesh, 0, sizeof( BoneMesh ) );

		boneMesh->OriginMesh = pMeshData->pMesh;
		pMeshData->pMesh->AddRef();
		boneMesh->MeshData.pMesh = pMeshData->pMesh;
		boneMesh->MeshData.Type = pMeshData->Type;

		IDirect3DDevice9* device = NULL;
		pMeshData->pMesh->GetDevice( &device );

		for(unsigned int i = 0; i < NumMaterials; i++ ){
			D3DXMATERIAL material;
			memcpy( &material, &pMaterials[ i ], sizeof( D3DXMATERIAL ) );
			boneMesh->materials.push_back( material.MatD3D );

			IDirect3DTexture9* texture = NULL;

			if( material.pTextureFilename != NULL ){
				NETStringSet parsed;
				NETString buffer(material.pTextureFilename);
				buffer.split("@", parsed);
				
				for(int n=0; n < parsed.getLength() ;n++)
				{
					NETString filepath = _work_directory + parsed[n];
					HRESULT test = D3DXCreateTextureFromFile(device, filepath.toCharPointer(), &texture);

					boneMesh->textures.push_back(texture);
					_face_count++;
				}
			}
		}

		if( pSkinInfo != NULL ){
			boneMesh->pSkinInfo = pSkinInfo; 

			pSkinInfo->AddRef();

			pMeshData->pMesh->CloneMeshFVF( D3DXMESH_MANAGED, pMeshData->pMesh->GetFVF(), device, &boneMesh->MeshData.pMesh );

			boneMesh->MeshData.pMesh->GetAttributeTable( NULL, &boneMesh->NumAtttributeGroup );
			boneMesh->attributeTable = new D3DXATTRIBUTERANGE[ boneMesh->NumAtttributeGroup ];
			boneMesh->MeshData.pMesh->GetAttributeTable( boneMesh->attributeTable, NULL );

			int boneNumbers = pSkinInfo->GetNumBones();			
			boneMesh->pBoneOffsetMatrices = new D3DXMATRIX[ boneNumbers ];
			for(int n=0; n < boneNumbers; n++)
				boneMesh->pBoneOffsetMatrices[n] = *( boneMesh->pSkinInfo->GetBoneOffsetMatrix(n));
		}

		*ppNewMeshContainer = boneMesh;
	
		if(device)
			device->Release();
		return S_OK;
	}
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);

	OnHierarchyLoad(ThisClass& owner, const NETString& work_directory)
		: _owner(owner), _work_directory(work_directory)
	{
		_face_count = 0;
	}
	HRESULT AllocateName( LPCSTR Name, LPSTR* pNewName )
	{
		UINT length;

		if( Name != NULL )
		{
			length = ( UINT )strlen( Name ) + 1;
			*pNewName = new CHAR[length];
			if( *pNewName == NULL )
				return E_OUTOFMEMORY;
			memcpy( *pNewName, Name, length * sizeof ( CHAR ) );
		}
		else
			*pNewName = NULL;

		return S_OK;
	}
	type_ubyte getFaceCount() const { return _face_count; }

private:
	ThisClass& _owner;
	NETString _work_directory;
	type_ubyte _face_count;
};