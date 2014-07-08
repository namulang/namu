#include "RayGenerator.hpp"
#include "../Mesh/Mesh.hpp"
#include "../DX9/DX9.hpp"
#include "../PerspectiveCamera/PerspectiveCamera.hpp"
#include "../Referer/Referer.hpp"

namespace DX9Graphics
{
	const NEExportable::ModuleHeader NE_DLL &RayGenerator::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T("RayGenerator.dev.dbg");
			_header.getDeveloper() = _T("kniz");
			_header.setRevision(1);
			_header.getComment() = _T("0번. 윈도우\n1번. 레퍼러\n2번. 카메라");
			_header.getVersion()  = _T("0.0.1a");
			_header.getReleaseDate() = _T("");
			_header.getModuleDependencies().create(0);
			_header.setMaxErrorCodeCount(1);
		}

		return _header;
	}

	RayGenerator::Ray RayGenerator::_createRayInViewMatrix(Camera& camera)
	{
		//	pre:
		//		타겟팅:
		Ray ray;
		ZeroMemory(&ray, sizeof(Ray));
		POINT& point = _computeScreenCursorPosition();
		D3DVIEWPORT9 vp = camera.createViewPort();
		D3DXMATRIX proj = camera.createProjectionMatrix();		
		
		
		
		//	main:
		//		변수 정의:
		float px = 0.0f;
		float py = 0.0f;		

		px = ((( 2.0f * point.x) / vp.Width)  - 1.0f) / proj(0, 0);
		py = (((-2.0f * point.y) / vp.Height) + 1.0f) / proj(1, 1);

		
		ray.center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ray.direction = D3DXVECTOR3(px, py, 1.0f);

		return ray;
	}

	Camera& RayGenerator::_castCamera()
	{
		static type_code perspective_camera = Kernal::getInstance().getModuleManager()
			.getModule(PerspectiveCamera().getHeader()) 
			.getScriptCode();
		NEModuleSelector& camera_selector = getConnector().getCameraSelector();
		
		NEModule* iterator = NE_NULL;
		camera_selector.initializeReferingPoint();
		while( iterator = &camera_selector.getModule())
		{
			if(iterator->getScriptCode() == perspective_camera)
			{
				Camera& camera = static_cast<Camera&>(*iterator);
				return camera;
			}
		}

		Camera* nullpoint = NE_NULL;
		return *nullpoint;
	}

	RenderableResource& RayGenerator::_getBindedFromReferer(Referer& referer)
	{
		RenderableResource* nullpoint = 0;
		if( ! &referer)
		{
			ALERT_ERROR(" : 레퍼러가 없음");
			return *nullpoint;
		}



		NEModuleBinder& binder = referer.getResourceBinder();
		if( ! binder.isBinded())			
			return *nullpoint;
		return static_cast<RenderableResource&>(binder.getBinded());
	}

	POINT RayGenerator::_computeScreenCursorPosition()
	{
		POINT	point = {0, 0};
		Window& window = getDependent();
		if( ! &window)
		{
			ALERT_ERROR(" : 윈도우가 없음");
			return point;
		}

		GetCursorPos(&point);
		ScreenToClient(window.getHWND(), &point);

		return point;
	}
}