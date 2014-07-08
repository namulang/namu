#include "Mesh.hpp"
#include "define/define.hpp"
#include "../DX9/DX9.hpp"
#include "../PerspectiveCamera/PerspectiveCamera.hpp"

namespace DX9Graphics
{
	const NEExportable::ModuleHeader& Mesh::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T(_NAME);
			_header.getDeveloper() = _T(_DEVELOPER);
			_header.setRevision(_REVISION);
			_header.getComment() = _T(_COMMENT);
			_header.getVersion()  = _T(_VERSION);
			_header.getReleaseDate() = _T(_DATE);
			_header.getModuleDependencies().create(_DEPENDENCIES_COUNT);
			_header.setMaxErrorCodeCount(1);
		}

		return _header;
	}

	type_result Mesh::_loadMeshFromX(NETString& path)
	{

		//	pre:
		//		작업 경로 획득:
		NETString& work_directory = _createWorkDirectory(path);
		//		타겟팅:
		DX9& dx9 = getDependent();
		if( ! &dx9)
		{
			ALERT_ERROR(" : 디바이스를 얻지 못했으므로, 메시를 로드할 수 없습니다.");
			return RESULT_TYPE_ERROR;
		}
		LPDIRECT3DDEVICE9 device = dx9.getDevice();



		//	main:
		LPD3DXBUFFER temporary_material_buffer = NE_NULL;
		DWORD material_count = 0;

		if( FAILED(D3DXLoadMeshFromX(path.toCharPointer(), D3DXMESH_SYSTEMMEM,	device, NULL, &temporary_material_buffer, NULL, &material_count, &_mesh)) )
		{
			ALERT_ERROR(" : 메시를 로드 하지 못했습니다.\n경로가 잘못된 것은 아닌가요?\n\t경로: %s", path.toCharPointer());
			return RESULT_TYPE_ERROR;
		}

		D3DXMATERIAL* d3dxMaterials = ( D3DXMATERIAL* )temporary_material_buffer->GetBufferPointer();

		for( DWORD i = 0; i < material_count; i++ )
		{
			// Copy the material
			_materiallist.push(d3dxMaterials[i].MatD3D);

			// Set the ambient color for the material (D3DX does not do this)
			D3DMATERIAL9& inputed = _materiallist[_materiallist.getLengthLastIndex()];
			inputed.Ambient = inputed.Diffuse;

			if( d3dxMaterials[i].pTextureFilename != NULL &&
				lstrlenA( d3dxMaterials[i].pTextureFilename ) > 0 )
			{
				IDirect3DTexture9* texture = NE_NULL;
				// Create the texture
				NETString new_path = work_directory + d3dxMaterials[i].pTextureFilename;
				if( FAILED(D3DXCreateTextureFromFile(device, new_path.toCharPointer(),
					&texture)) )
				{
					ALERT_ERROR(" : 텍스쳐를 로드 하지 못했습니다.\n경로가 잘못된 것은 아닌가요?\n\t경로: %s", NETString(d3dxMaterials[i].pTextureFilename).toCharPointer());
					return RESULT_TYPE_ERROR;
				}

				_texturelist.push(texture);
			}
		}

		// Done with the material buffer
		temporary_material_buffer->Release();

		return RESULT_SUCCESS;
	}

	type_result Mesh::render()
	{
		if( ! isEnable())
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		//	pre:
		//		디바이스 획득:
		DX9& dx9 = getDependent();
		if( ! &dx9) return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		LPDIRECT3DDEVICE9 device = dx9.getDevice();



		//	main:
		//		드로잉:
		MaterialList::Iterator* material = _materiallist.getIterator(0);
		TextureList::Iterator* texture = _texturelist.getIterator(0);
		int n=0;
		while(material && texture)
		{
			//		리소스 세팅:
			device->SetMaterial( &material->getValue());
			device->SetTexture(0, &texture->getValue());
			//		드로잉:
			//PerspectiveCamera& camera = PerspectiveCamera::getRenderingCamera();
			//camera.getShadowShader().RenderStart(camera);
			//_mesh->DrawSubset(n);
			//camera.getShadowShader().RenderEnd(camera);
			//camera.getOutlineShader().RenderStart(camera);
			_mesh->DrawSubset(n++);
			//camera.getOutlineShader().RenderEnd(camera);
			//		반복자 이동:
			material = material->getNext();
			texture = texture->getNext();
		}

		return RESULT_SUCCESS;
	}

	type_result Mesh::renderOnPicked()
	{
		if( ! isEnable())
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		//	pre:
		//		디바이스 획득:
		DX9& dx9 = getDependent();
		if( ! &dx9) return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		LPDIRECT3DDEVICE9 device = dx9.getDevice();



		//	main:
		//		드로잉:
		TextureList::Iterator* texture = _texturelist.getIterator(0);
		int n=0;
		D3DMATERIAL9 material_on_picked;
		_setD3DColorToRed(material_on_picked.Ambient);
		_setD3DColorToRed(material_on_picked.Diffuse);
		_setD3DColorToRed(material_on_picked.Specular);
		_setD3DColorToRed(material_on_picked.Emissive);
		while(texture)
		{
			//		리소스 세팅:		
			device->SetMaterial( &material_on_picked);
			device->SetTexture(0, &texture->getValue());
			//		드로잉:
			_mesh->DrawSubset(n++);
			//		반복자 이동:
			texture = texture->getNext();
		}

		return RESULT_SUCCESS;
	}

	type_result Mesh::renderOnHover()
	{
		if( ! isEnable())
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		//	pre:
		//		디바이스 획득:
		DX9& dx9 = getDependent();
		if( ! &dx9) return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		LPDIRECT3DDEVICE9 device = dx9.getDevice();



		//	main:
		//		드로잉:
		TextureList::Iterator* texture = _texturelist.getIterator(0);
		int n=0;
		D3DMATERIAL9 material_on_picked;
		_setD3DColorToGreen(material_on_picked.Ambient);
		_setD3DColorToGreen(material_on_picked.Diffuse);
		_setD3DColorToGreen(material_on_picked.Specular);
		_setD3DColorToGreen(material_on_picked.Emissive);
		while(texture)
		{
			//		리소스 세팅:		
			device->SetMaterial( &material_on_picked);
			device->SetTexture(0, &texture->getValue());
			//		드로잉:
			_mesh->DrawSubset(n++);
			//		반복자 이동:
			texture = texture->getNext();
		}

		return RESULT_SUCCESS;
	}
}