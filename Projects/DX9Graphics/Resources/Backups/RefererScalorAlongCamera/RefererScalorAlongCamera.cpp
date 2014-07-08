#include "RefererScalorAlongCamera.hpp"
#include "../Referer/Referer.hpp"
#include "../../../../WindowModules/Sources/WindowModule/Sources/EntryPoints/Headers.hpp"

namespace DX9Graphics
{
	void RefererScalorAlongCamera::_computeCombinedMatrix(Referer& referer, Camera& camera)
	{
		//	pre:
		//		타겟팅:		
		NE::Window& window = getDependent();
		if( ! &window)
		{
			ALERT_ERROR(" : 마우스 스파이 에러!");
			return;
		}
		USHORT simultenoused_press = LOWORD(window.getMSG().wParam);
		type_int message = window.getMSG().message;		
		if(message != WM_MOUSEWHEEL) return;
		if(simultenoused_press & MK_RBUTTON) return;
		//			Z 계산:		
		//				계산:
		//				양수면 앞쪽으로 한클릭 움직인 것을 의미한다.
		//				0 ~ 120 사이의 값을 갖는다.
		SHORT wheel_degree = HIWORD(window.getMSG().wParam);
		float referer_scale = D3DXVec3Length(&D3DXVECTOR3(referer.getScaleMatrix()._11, referer.getScaleMatrix()._12, referer.getScaleMatrix()._13));
		float click = wheel_degree > 0 ? 1.1f : 0.9f;
		if((GetAsyncKeyState(VK_SPACE)) & 0x8000)
			click = wheel_degree > 0 ? 1.3f : 0.7f;
		
		referer_scale *= click;
		//		매트릭스 적용:
		D3DXMatrixScaling(&referer.getScaleMatrix(), referer_scale, referer_scale, referer_scale);		
	}

	type_result RefererScalorAlongCamera::execute()
	{
		//	pre:
		//		타겟팅:
		Camera& camera = _castCamera();
		if( ! &camera)
		{
			ALERT_ERROR(" : 카메라가 없음");
			return RESULT_TYPE_ERROR;
		}
		Referer& referer = Referer::getGlobalReferer();
		if( ! &referer) return RESULT_TYPE_ERROR;	



		//	main:
		//		적용:
		_computeCombinedMatrix(referer, camera);

		//	post:
		return RESULT_SUCCESS;
	}
}