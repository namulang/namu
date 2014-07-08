#include "HierarchySubReferer.hpp"
#include "../PerspectiveCamera/PerspectiveCamera.hpp"

namespace DX9Graphics
{
	type_result HierarchySubReferer::_render( D3DMATERIAL9& material )
	{
		_initializeMesh();
		//	main:
		//		DX9 바인딩:
		DX9& dx9 = getDependent();
		if( ! &dx9)
		{
			ALERT_ERROR(" : 디바이스 바인딩 실패로 중지");
			return RESULT_TYPE_ERROR;
		}
		LPDIRECT3DDEVICE9 device = dx9.getDevice();		
		//		월드좌표 갱신:
		D3DXMATRIX& world = getWorldMatrix();
		D3DXMATRIX origin;
		device->GetTransform(D3DTS_WORLD, &origin);
		device->SetTransform(D3DTS_WORLD, &world);

		device->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

		//device->SetTexture(0, NULL);
		device->SetMaterial(&material);
		device->SetTexture(0, 0);
		if(_ball)
		{			
			_ball->DrawSubset(0);
		}

		//		자식과 선을 잇기:
		device->SetTransform(D3DTS_WORLD, &origin);

		_searchModuleSet(getConnector().getModuleCodeSetKey().getValue(), &ThisClass::_renderLineBetweenChild);			//		월드 좌표 복귀:
		return RESULT_SUCCESS;
	}
}