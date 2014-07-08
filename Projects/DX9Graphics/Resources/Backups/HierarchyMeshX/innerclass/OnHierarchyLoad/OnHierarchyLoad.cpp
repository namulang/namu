#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#endif

#include "../../HierarchyMeshX.hpp"

namespace DX9Graphics
{
	HRESULT HierarchyMeshX::OnHierarchyLoad::DestroyFrame(LPD3DXFRAME pFrameToFree)
	{
		SAFE_DELETE_ARRAY(pFrameToFree->Name);		
		return S_OK;
	}

	HRESULT HierarchyMeshX::OnHierarchyLoad::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
	{
		BoneMesh* mesh = (BoneMesh*) pMeshContainerBase;

		SAFE_DELETE_ARRAY(mesh->Name);
		SAFE_DELETE_ARRAY(mesh->pAdjacency);
		SAFE_DELETE_ARRAY(mesh->pMaterials);		
		SAFE_DELETE_ARRAY(mesh->pBoneOffsetMatrices);
		SAFE_DELETE_ARRAY(mesh->attributeTable);

		// release all the allocated textures
		std::vector< IDirect3DTexture9*>::iterator i;
		for(i=mesh->textures.begin(); i != mesh->textures.end() ;i++)
			if(*i)
				(*i)->Release();

		SAFE_RELEASE( mesh->MeshData.pMesh );
		SAFE_RELEASE( mesh->pSkinInfo );
		SAFE_RELEASE( mesh->OriginMesh );
		SAFE_DELETE( mesh );
		return S_OK;
	}
}