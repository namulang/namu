#include "RefererTransitorAlongCamera.hpp"
#include "../Mesh/Mesh.hpp"
#include "../DX9/DX9.hpp"
#include "../PerspectiveCamera/PerspectiveCamera.hpp"
#include "../Referer/Referer.hpp"
namespace DX9Graphics
{
	const NEExportable::ModuleHeader& RefererTransitorAlongCamera::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T("RefererTransitorAlongCamera.dev.dbg");
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

	void RefererTransitorAlongCamera::_computeCombinedMatrix(Referer& referer, Camera& camera, RayGenerator::Ray& ray, DWORD message)
	{
		//	타겟팅:
		D3DXMATRIX	&	mesh_transition = referer.getTransitionMatrix(),
					&	mesh_parent_world = referer.getParentWorldMatrix();
		D3DXVECTOR3 mesh_center(mesh_transition._41, mesh_transition._42, mesh_transition._43);
		D3DXVECTOR3& plane_normal = camera.createLookVector();
		D3DXPLANE mesh_plane;
		D3DXPlaneFromPointNormal(&mesh_plane, &mesh_center, &plane_normal);

		D3DXVECTOR3& intersected_point = _computeIntersectedPoint(mesh_plane, ray);

		static D3DXMATRIX _first_transition;
		static D3DXVECTOR3 _first_point;
		if(message == WM_LBUTTONDOWN)
		{
			_first_transition = mesh_transition;
			_first_transition._43 = 0.0f;
			_first_point = intersected_point;
			_first_point.z = 0.0f;
		}
		else if(message == WM_MOUSEMOVE)
		{
			D3DXMATRIX moved;
			D3DXVECTOR3 term = intersected_point - _first_point;
			term.z = 0.0f;
			D3DXMatrixTranslation(&moved, term.x, term.y, term.z);
			mesh_transition = _first_transition * moved;			
		}
	}

	type_result RefererTransitorAlongCamera::execute()
	{
		//	pre:
		//		타겟팅:
		NEKeyCodeSet& keyset = getKeySet();
		Camera& camera = _castCamera();
		if( ! &camera)
		{
			ALERT_ERROR(" : 카메라가 없음");
			return RESULT_TYPE_ERROR;
		}
		Referer& referer = Referer::getGlobalReferer();
		Window& window = getDependent();
		if( ! &window)
		{
			ALERT_ERROR(" : 윈도우가 없음");
			return RESULT_TYPE_ERROR;
		}
		const MSG& msg = window.getMSG();
		if(msg.message != WM_LBUTTONDOWN && msg.message != WM_MOUSEMOVE && msg.message != WM_LBUTTONUP)
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		if(	msg.message == WM_MOUSEMOVE			&&
			! (LOWORD(msg.wParam) & MK_LBUTTON)	)
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;



		//	main:
		//		스크린 상의 X, Y 구하기:
		//		광선 구하기:
		//			스크린좌표로 광선을 구하기:
		RayGenerator::Ray ray = _createRayInViewMatrix(camera);
		D3DXMATRIX	viewMat = camera.createViewMatrix(), 
					viewInverse;
		D3DXMatrixInverse(&viewInverse, 0, &viewMat);
		_transformRayToOtherSpace(ray, viewInverse);
		ray.direction.x *= 30.0f;
		ray.direction.y *= 30.0f;
		ray.direction.z *= 30.0f;
	
		//		적용:
		if( ! &referer) 
			return _transitCamera(ray, msg.message);
		else
			_computeCombinedMatrix(referer, camera, ray, msg.message);

		//	post:
		return RESULT_SUCCESS;
	}

	D3DXVECTOR3 RefererTransitorAlongCamera::_computeIntersectedPoint(D3DXPLANE& plane, RayGenerator::Ray& ray)
	{
		D3DXVECTOR3 intersected;
		D3DXPlaneIntersectLine(&intersected, &plane, &ray.center, &ray.direction);

		return intersected;
	}

	type_result RefererTransitorAlongCamera::_transitCamera(RayGenerator::Ray& ray, DWORD message)
	{
		NEModuleSelector s;
		s.setNodeType(NECodeType::ALL);
		NECodeSet c(1);
		static type_code camera_code = Kernal::getInstance().getModuleManager()
			.getModule(PerspectiveCamera().getHeader()).getScriptCode();
		c.push(camera_code);
		s.setModuleType(NECodeType::SCRIPT);
		s.setModuleCodeSet(c);

		while( &s.getModule() )
		{
			PerspectiveCamera& cam = (PerspectiveCamera&) s.peekModule();
			if(	! cam.is_picked											||
				cam.getConnector().getIsViewportMaxmized().getValue()	)
				continue;

			//	타겟팅:
			static POINT _first_transition;
			static POINT _first_point;
			POINT pos;
			GetCursorPos(&pos);
			if(message == WM_LBUTTONDOWN)
			{
				_first_transition.x = cam.getConnector().getViewPortX().getValue();
				_first_transition.y = cam.getConnector().getViewPortY().getValue();
				_first_point = pos;
			}
			else if(message == WM_MOUSEMOVE)
			{
				DWORD termx = 0, termy = 0;
				termx = pos.x - _first_point.x;
				termy = pos.y - _first_point.y;
				cam.getConnector().getViewPortX().getValue() = _first_transition.x + termx;
				cam.getConnector().getViewPortY().getValue() = _first_transition.y + termy;
			}
		}

		return RESULT_SUCCESS;
	}
}