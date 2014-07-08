#pragma warning(disable: 4700)
#include "HierarchyMeshX.hpp"
#pragma warning(default: 4700)
#include "../HierarchyReferer/HierarchyReferer.hpp"
#include "../PerspectiveCamera/PerspectiveCamera.hpp"

namespace DX9Graphics
{
	type_result HierarchyMeshX::render()
	{
		if( ! isEnable())
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		DX9& dx9 = getDependent();
		if( ! &dx9)
		{
			ALERT_ERROR(" : DX9가 없습니다");
			return RESULT_TYPE_ERROR;
		}
		
		PerspectiveCamera& camera = PerspectiveCamera::getRenderingCamera();
		camera.getShadowShader().RenderStart(camera);
		type_result result = _renderByReculsive(getRootFrame(), 0, dx9.getDevice(), 0);
		camera.getShadowShader().RenderEnd(camera);

		camera.getOutlineShader().RenderStart(camera);
		result |= _renderByReculsive(getRootFrame(), 0, dx9.getDevice(), 0);
		camera.getOutlineShader().RenderEnd(camera);

		return result;
	}

	type_result HierarchyMeshX::renderOnPicked()
	{
		if( ! isEnable())
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		DX9& dx9 = getDependent();
		if( ! &dx9)
		{
			ALERT_ERROR(" : DX9가 없습니다");
			return RESULT_TYPE_ERROR;
		}

		return _renderByReculsive(getRootFrame(), 1, dx9.getDevice(), 0);
	}

	type_result HierarchyMeshX::_renderByReculsive(BoneFrame& mesh, type_byte status, LPDIRECT3DDEVICE9 device, int container_n)
	{
		if( ! &_referer->getFinalWorldsSet()) return RESULT_TYPE_ERROR;
		if(GetAsyncKeyState(VK_SPACE) & 0x8001) return RESULT_SUCCESS;
		static D3DMATERIAL9 red_material = {
								{1.0f, 0.0f, 0.0f, 1.0f}, 
								{1.0f, 0.0f, 0.0f, 1.0f},
								{1.0f, 0.0f, 0.0f, 1.0f},
								{1.0f, 0.0f, 0.0f, 1.0f},
								5.0f
							},
							green_material = {
								{0.0f, 1.0f, 0.0f, 1.0f}, 
								{0.0f, 1.0f, 0.0f, 1.0f},
								{0.0f, 1.0f, 0.0f, 1.0f},
								{0.0f, 1.0f, 0.0f, 1.0f},
								5.0f
							};
		if( ! &mesh) return RESULT_TYPE_ERROR;
		if(mesh.pMeshContainer) 
		{
			BoneMesh& boneMesh = (BoneMesh&)*mesh.pMeshContainer;

			if(boneMesh.pSkinInfo)
			{
				BYTE *temp, *dest = NULL;
				boneMesh.OriginMesh->LockVertexBuffer( D3DLOCK_READONLY, ( VOID** )&temp);
				boneMesh.MeshData.pMesh->LockVertexBuffer( 0, ( VOID** )&dest );

				boneMesh.pSkinInfo->UpdateSkinnedMesh(&_referer->getFinalWorldsSet()[container_n][0], NULL, temp, dest);
 
				boneMesh.OriginMesh->UnlockVertexBuffer();
				boneMesh.MeshData.pMesh->UnlockVertexBuffer();

				for(unsigned int i = 0; i < boneMesh.NumAtttributeGroup; i++) 
				{
					int mtrl = boneMesh.attributeTable[i].AttribId;

					switch(status)
					{
					case 1:
						device->SetMaterial(&red_material);
						break;

					case 2:
						device->SetMaterial(&green_material);
						break;

					default:
						boneMesh.materials[mtrl].Ambient.a = 1.0f;
						boneMesh.materials[mtrl].Ambient.r = 1.0f;
						boneMesh.materials[mtrl].Ambient.g = 1.0f;
						boneMesh.materials[mtrl].Ambient.b = 1.0f;
						device->SetMaterial( &(boneMesh.materials[mtrl]) );
					}
					
					if(getFaceType() < boneMesh.textures.size())
						device->SetTexture(0 , boneMesh.textures[getFaceType()]);
					else
						device->SetTexture(0 , boneMesh.textures[mtrl]);
					boneMesh.MeshData.pMesh->DrawSubset(mtrl);
				}

				container_n++;
			}
		}


		if(mesh.pFrameSibling != NULL )
			_renderByReculsive( *((BoneFrame*)mesh.pFrameSibling), status, device, container_n);

		if(mesh.pFrameFirstChild != NULL )
			_renderByReculsive( *((BoneFrame*)mesh.pFrameFirstChild), status, device, container_n);

		return RESULT_SUCCESS;
	}

	type_result HierarchyMeshX::renderOnHover()
	{
		if( ! isEnable())
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		DX9& dx9 = getDependent();
		if( ! &dx9)
		{
			ALERT_ERROR(" : DX9가 없습니다");
			return RESULT_TYPE_ERROR;
		}

		return _renderByReculsive(getRootFrame(), 2, dx9.getDevice(), 0);
	}

	type_result HierarchyMeshX::setHierarchyReferer(HierarchyReferer& source)
	{
		_referer = &source;

		return RESULT_SUCCESS;
	}

	const NEExportable::ModuleHeader& HierarchyMeshX::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T("HierarchyMeshX.dev.dbg");
			_header.getDeveloper() = _T("kniz");
			_header.setRevision(1);
			_header.getComment() = _T("0번: 모듈셀렉터로 DX9바인딩한다.\n1번: 메시 파일의 경로");
			_header.getVersion()  = _T("0.0.1a");
			_header.getReleaseDate() = _T("");
			_header.getModuleDependencies().create(0);
			_header.setMaxErrorCodeCount(1);
		}

		return _header;
	}
}