#include "RefererRotatorAlongCamera.hpp"
#include "../Mesh/Mesh.hpp"
#include "../DX9/DX9.hpp"
#include "../PerspectiveCamera/PerspectiveCamera.hpp"
#include "../Referer/Referer.hpp"
#include "../../../../WindowModules/Sources/WindowModule/Sources/EntryPoints/Headers.hpp"

namespace DX9Graphics
{
	const NEExportable::ModuleHeader& RefererRotatorAlongCamera::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T("RefererRotatorAlongCamera.dev.dbg");
			_header.getDeveloper() = _T("kniz");
			_header.setRevision(1);
			_header.getComment() = _T("0번. 윈도우\n1번. 레퍼러\n2번. 카메라 모듈셀렉터");
			_header.getVersion()  = _T("0.0.1a");
			_header.getReleaseDate() = _T("");
			_header.getModuleDependencies().create(0);
			_header.setMaxErrorCodeCount(1);
		}

		return _header;
	}

	void RefererRotatorAlongCamera::_computeCombinedMatrix(Referer& referer, Camera& camera)
	{
		//	pre:
		//		타겟팅:	
		bool is_control_light = false;
		if( ! &referer) 
			if(GetAsyncKeyState(VK_TAB) < 0)
				is_control_light = true;
			else
				return;

		NE::Window& window = getDependent();
		if( ! &window)
		{
			ALERT_ERROR(" : 마우스 스파이 에러!");
			return;
		}
		USHORT simultenoused_press = LOWORD(window.getMSG().wParam);
		type_uint message = window.getMSG().message;		
		if(	message != WM_MOUSEMOVE		&&
			message != WM_MOUSEWHEEL	&&
			message != WM_RBUTTONDOWN	)
			return;
		if( message != WM_RBUTTONDOWN			&&
			! (simultenoused_press & MK_RBUTTON)) return;
		POINT& cursor = _computeScreenCursorPosition();
		D3DVIEWPORT9& viewport = camera.createViewPort();
		
		//		수치 계산:
		POINT center_of_screen;
		center_of_screen.x = viewport.X + (LONG)(viewport.Width * 0.5);
		center_of_screen.y = viewport.Y + (LONG)(viewport.Height * 0.5);
		//		커서와 중앙의 차이:
		POINT delta_point;
		delta_point.x = center_of_screen.x - cursor.x;
		delta_point.y = center_of_screen.y - cursor.y;
		//			Z 계산:		
		//				계산:
		SHORT wheel_degree = 0;
		if(message == WM_MOUSEWHEEL)
		{
			wheel_degree = HIWORD(window.getMSG().wParam);
			_z_radian += ((float)wheel_degree / 119) * (3.14f / 18.0f);
		}
		//				양수면 앞쪽으로 한클릭 움직인 것을 의미한다.
		//				0 ~ 120 사이의 값을 갖는다.
		//		차이를 radian으로 계산:
		//			x는 y-rotate, y는 x-rotate:
		float	x_radian = ((float) delta_point.y / (viewport.Height / 4)) * 3.14f,
				y_radian = ((float) delta_point.x / (viewport.Width / 4)) * 3.14f;
		
		//		매트릭스 적용:
		D3DXMATRIX x, y, z;
		D3DXMatrixRotationX(&x, x_radian);
		D3DXMatrixRotationY(&y, y_radian);
		D3DXMatrixRotationZ(&z, _z_radian);
		if(is_control_light)
		{
			//	광원을 rotate 한다.
			D3DXMATRIX combined = x * y * z;
			D3DXVECTOR3 light_base(-1.0f, 0.0f, 0.0f);	
			D3DXVECTOR4 applied;
			D3DXVec3Transform(&applied, &light_base, &combined);
			PerspectiveCamera::Connector& connector = static_cast<PerspectiveCamera&>(camera).getConnector();
			connector.getLightX() = applied.x;
			connector.getLightY() = applied.y;
			connector.getLightZ() = applied.z;
		}
		else
		{
			D3DXMATRIX& rotate = referer.getRotationMatrix();
			
			rotate = x * y * z;
		}		
	}

	type_result RefererRotatorAlongCamera::execute()
	{
		//	pre:
		//		타겟팅:
		Camera& camera = _castCamera();
		if( ! &camera)
		{
			ALERT_ERROR(" : 카메라가 없음");
			return RESULT_TYPE_ERROR;
		}



		//	main:
		Referer& referer = Referer::getGlobalReferer();
		_computeCombinedMatrix(referer, camera);

		//	post:
		return RESULT_SUCCESS;
	}

}