#include "Camera.hpp"
#include "../DX9/DX9.hpp"
#include "../PerspectiveCamera/PerspectiveCamera.hpp"
#include <math.h>

namespace DX9Graphics
{
	type_result Camera::_applyViewMatrix()
	{
		const D3DXMATRIX& view_matrix = getViewMatrix();
		DX9& dx9 = _getBinded();
		if( ! &dx9)
		{
			ALERT_ERROR(" : DX9가 바인딩 되어있지 않으므로 작업을 취소합니다.");
			return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		}
		LPDIRECT3DDEVICE9 device = dx9.getDevice();
		


		//	post:		
		device->SetTransform(D3DTS_VIEW, &view_matrix);
		return RESULT_SUCCESS;
	}

	void Camera::_setModuleCodeSet(NEModuleSelector& selector)
	{	
		selector.setModuleCodeSet(getCameraCodeSet());
		selector.setModuleType(NECodeType::SCRIPT);
	}

	type_result Camera::_setViewPort()
	{
		DX9& dx9 = _getBinded();
		if( ! &dx9)
		{
			ALERT_ERROR(" : DX9가 바인딩 되어있지 않으므로 작업을 취소합니다.");
			return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		}
		LPDIRECT3DDEVICE9 device = dx9.getDevice();



		//	main:
		if(isViewportMaximized())
			device->SetViewport(&createMaximizedViewPort());
		else
			device->SetViewport(&createViewPort());
		return RESULT_SUCCESS;
	}

	const NECodeSet& Camera::getCameraCodeSet()
	{
		static NECodeSet codeset;
		if(codeset.getLength() <= 0)
		{
			NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
			codeset.create(1);
			codeset.setCodeType(NECodeType::SCRIPT);
			codeset.push(PerspectiveCamera().getHeader());
		}

		return codeset;
	}

	DX9& Camera::_getBinded()
	{
		NEModuleSelector& sel = getDX9Selector();

		if( ! sel.getBinder().isBinded())
		{			
			static type_code dx9_code = Kernal::getInstance().getModuleManager()
				.getModule(DX9().getHeader()).getScriptCode();

			while(NEModule* itr = &sel.getModule())
				if(itr->getScriptCode() == dx9_code)
				{
					sel.bind();
					sel.initializeReferingPoint();
					goto POST;
				}

			ALERT_WARNING("DX9 바인딩 실패");
		}

POST:
		return (DX9&) sel.getBinder().getBinded();
	}

	const DX9& Camera::_getBinded() const
	{
		return (const DX9&) getDX9Selector().getBinder().getBinded();
	}

	void Camera::EulerAngles::fromVector(const D3DXVECTOR3& look)
	{
		//	main:
		//		좌표 예측 알고리즘:
		//			Euler->XYZ Coordinates 공식을 arcsin을 사용해서 역산한다.
		//			삼각함수는 비가역이므로, asin시 가능한 정의역은 무수히 많다.
		//			여기서는 0 ~ 2PI로 가정(실제로는 -PI/2 ~ 3/2PI)하므로 가능한
		//			정의역은 2 or 3개로 압축된다. (asin(0)할때 3개)
		//			그렇게 asin할때마다 모든 경우의 수로 Euler->XYZ 공식에 대입
		//			하여 올바른 값이 도출되는지 확인한다.				
		type_float	x_rad = 0.0f,
			y_rad = 0.0f,
			cosx = 0.0f;

		//		시도 1:
		x_rad = asinf(-look.y);
		//			시도 1-1:
		y_rad = asinf(look.x / cosf(x_rad));
		if(_isPredictionOfEulerConversionRight(x_rad, y_rad, look.z))
			goto POST;
		//			시도 1-2:
		y_rad = D3DX_PI - y_rad;
		if(_isPredictionOfEulerConversionRight(x_rad, y_rad, look.z))
			goto POST;

		//		시도 2:
		x_rad = D3DX_PI - x_rad;
		//			시도 2-1:
		y_rad = asinf(look.x / cosf(x_rad));
		if(_isPredictionOfEulerConversionRight(x_rad, y_rad, look.z))
			goto POST;
		//			시도 2-2:
		y_rad = D3DX_PI - y_rad;
		if(_isPredictionOfEulerConversionRight(x_rad, y_rad, look.z))
			goto POST;

		KERNAL_ERROR("잘못된 XYZ Coordinates --> EulerAngles 변환입니다");


		//	post:
POST:
		const type_float adjustment = 180.0f / D3DX_PI;
		x_axis_angle = x_rad * adjustment;
		y_axis_angle = y_rad * adjustment;
	}

	bool Camera::EulerAngles::_isPredictionOfEulerConversionRight(type_float predicted_x_radian, type_float predicted_y_radian, type_float right_answer) const
	{
		//	예측 검증:
		//		공식 : z-coordinate = cosx * cosy로, Z 좌표를 다시 검산해봄으로써
		//		주어진 예측이 맞는지 확인한다.
		type_float z = cosf(predicted_x_radian) * cosf(predicted_y_radian);
		return _isEqual(z, right_answer);
	}
}