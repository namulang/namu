#include "Particle.hpp"
#include "../DX9/DX9.hpp"

namespace DX9Graphics
{
	type_result Particle::adjustBlendingOption()
	{
		DX9& dx9 = DX9::getInstancedDX();
		if( ! &dx9)
			return ALERT_ERROR("DX9를 NodeManager에서 발견하지 못했습니다.");

		LPDIRECT3DDEVICE9 dev = dx9.getDevice();
		if( ! dev)
			return ALERT_WARNING("디바이스 초기화가 이루어지지 않았습니다.");

		switch(arg_blending.getValue())
		{
		case 0:	//	Normal
			dev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			break;

		case 1:	//	Darken
			dev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_MIN);
			dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;

		case 2:	//	Multple
			dev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
			dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
			break;

		case 3:	//	Lightn
			dev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_MAX);
			dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;

		case 4:	//	Screen
			dev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
			dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;

		case 5:	//	Subtract
			dev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;

		case 6:	//	Linear dodge
			dev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;

		default:
			return ALERT_WARNING("존재하지 않는 블렌딩 옵션입니다.");
		}

		return RESULT_SUCCESS;

	}
}