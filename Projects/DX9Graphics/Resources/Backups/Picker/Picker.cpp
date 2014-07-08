#include "Picker.hpp"
#include "../Mesh/Mesh.hpp"
#include "../DX9/DX9.hpp"
#include "../PerspectiveCamera/PerspectiveCamera.hpp"
#include "../Referer/Referer.hpp"
#include "../Sprite/Sprite.hpp"
#include "../HierarchyMeshX/HierarchyMeshX.hpp"
#include "../HierarchyReferer/HierarchyReferer.hpp"
#include "../HierarchySubReferer/HierarchySubReferer.hpp"
#include "../PerspectiveCamera/PerspectiveCamera.hpp"
#include "../SpriteReferer/SpriteReferer.hpp"
#include "../Pages/Pages.hpp"
#include <math.h>

namespace DX9Graphics
{
	const NEExportable::ModuleHeader& Picker::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T("Picker.dev.dbg");
			_header.getDeveloper() = _T("kniz");
			_header.setRevision(1);
			_header.getComment() = _T("0번. 윈도우\n1번. Referer\n2번. 카메라 모듈셀렉터");
			_header.getVersion()  = _T("0.0.1a");
			_header.getReleaseDate() = _T("");
			_header.getModuleDependencies().create(0);
			_header.setMaxErrorCodeCount(1);
		}

		return _header;
	}

	bool Picker::_isRayIntersected(Ray& ray, Mesh& mesh)
	{
		BOOL is_hit = 0;
		D3DXIntersect(&mesh.getMesh(), &(ray.center), &ray.direction, &is_hit, 0, 0, 0, 0, 0 ,0);

		return is_hit != 0;
	}

	float Picker::_extractScaleX(D3DXMATRIX& world)
	{
		D3DXVECTOR3 vector(world._11, world._12, world._13);
		return D3DXVec3Length(&vector);
	}
	float Picker::_extractScaleY(D3DXMATRIX& world)
	{
		D3DXVECTOR3 vector(world._21, world._22, world._23);
		return D3DXVec3Length(&vector);
	}

	bool Picker::_isRayIntersected(SuperClass::Ray& ray, Referer& referer, Sprite& sprite)
	{
		//	텍스쳐의 영역을 획득:
		//		Width와 Height에 Scale벡터를 적용한 뒤에 적용된 두 값의 평균값을 반지름으로 삼는다.
		//		Scale이 적용된 Width와 Height 계산:
		//			Scale 매트릭스는 x의 scale 요소(Sx)가 1행 1열, y의 scale 요소(Sy)는 2행 2열 식으로
		//			나열되어 있으므로 이 값만을 이용할 것이다.
		//	스케일 값 추출:
		//		4행은 Transition 행렬과 동일하다.
		//		1~3행을 각각 벡터로 놓고 길이(norms)를 구하면 이는 scale 값이라 한다.
		D3DXMATRIX& scale = referer.getWorldMatrix();
		float	scaled_half_width	= sprite.getHalfWidth() * _extractScaleX(scale),
				scaled_half_height	= sprite.getHalfHeight() * _extractScaleY(scale);
		//		계산한 값의 평균으로 반지름을 구함:
		float	radius = (scaled_half_width + scaled_half_height) * 0.5f;
		//	스프라이트의 중점을 획득:
		D3DXVECTOR3 center(referer.getTransitionMatrix()._41, referer.getTransitionMatrix()._42, referer.getTransitionMatrix()._43);
				
		//	광선의 x, y:
		D3DXVECTOR3 v = ray.center - center;

		float b = 2.0f * D3DXVec3Dot(&ray.direction, &v);
		float c = D3DXVec3Dot(&v, &v) - (radius*radius);

		float discriminant = (b * b) - (4.0f * c);

		if( discriminant < 0.0f)
			return false;

		discriminant = sqrtf(discriminant);

		float s0 = (-b + discriminant) / 2.0f;
		float s1 = (-b - discriminant) / 2.0f;

		if(s0 >= 0.0f || s1 >= 0.0f)
			return true;

		return false;
	}

	bool Picker::_isPicked(Referer& referer, Camera& camera)
	{
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();			
		static type_code mesh_code = moduler.getModule(Mesh().getHeader()).getScriptCode();
		static type_code sprite_code = moduler.getModule(Sprite().getHeader()).getScriptCode();
		static type_code hierarchy = moduler.getModule(HierarchyMeshX().getHeader()).getScriptCode();
		static type_code sub = moduler.getModule(HierarchySubReferer().getHeader()).getScriptCode();

		//	광선:
		//	광선을 Projection에서 View 좌표계로 변환:
  		Ray& ray = _createRayInViewMatrix(camera);
		//	광선을 View에서 World 좌표계로 변환:
		D3DXMATRIX viewMat, viewInverse;
		viewMat = camera.createViewMatrix();				
		D3DXMatrixInverse(&viewInverse, 0, &viewMat);
		_transformRayToOtherSpace(ray, viewInverse);
		
		if(referer.getScriptCode() == sub)
		{
			if(	! (GetAsyncKeyState(VK_SPACE) & 0x8001))
				return false;
			//	스페이스를 눌렀다면:
			D3DXMATRIX inversed_world;
			D3DXMatrixInverse(&inversed_world, 0, &referer.getWorldMatrix());
			_transformRayToOtherSpace(ray, inversed_world);

			return _isPicked(static_cast<HierarchySubReferer&>(referer), ray);
		}

		if(GetAsyncKeyState(VK_SPACE) & 0x8001)
			return false;
		RenderableResource& resource = _getBindedFromReferer(referer);
		if( ! &resource)
		{
			ALERT_ERROR(" : 리소스가 널 반환");
			return false;
		}
		if(	resource.getScriptCode() != mesh_code	&&
			resource.getScriptCode() != sprite_code	&&
			resource.getScriptCode() != hierarchy	)
			return false;
		
		//	main:

		if(resource.getScriptCode() == mesh_code)
		{
			Mesh& mesh = static_cast<Mesh&>(resource);

			//	광선을 World에서 Mesh의 로컬좌표계로 변환:
			//		D3DXIntersect는 mesh의 로컬좌표계에서만
			//		검사를 하기 때문이다.
			D3DXMATRIX inversed_world;
			D3DXMatrixInverse(&inversed_world, 0, &referer.getWorldMatrix());
			_transformRayToOtherSpace(ray, inversed_world);

			return _isRayIntersected(ray, mesh);
		}
		else if(resource.getScriptCode() == sprite_code)
		{
			Sprite& sprite = static_cast<Sprite&>(resource);

			//	광선을 World에서 Mesh의 로컬좌표계로 변환:
			//		D3DXIntersect는 mesh의 로컬좌표계에서만
			//		검사를 하기 때문이다.
			D3DXMATRIX inversed_world;
			D3DXMatrixInverse(&inversed_world, 0, &referer.getWorldMatrix());
			_transformRayToOtherSpace(ray, inversed_world);

			return _isRayIntersected(ray, referer, sprite);
		}
		else if(resource.getScriptCode() == hierarchy)
		{
			HierarchyMeshX& mesh = static_cast<HierarchyMeshX&>(resource);

			//	Hierarchy는 DX에서 메쉬정보를 업데이트 해버리므로 바로 적용이 가능하다

			bool result = _isRayIntersected(ray, mesh, mesh.getRootFrame()) == 1 ? true : false;
			return result;
		}

		ALERT_ERROR(" : 잘못된 타입");
		return false;
	}

	bool Picker::_isPicked( HierarchySubReferer& sub, SuperClass::Ray& ray )
	{
		//	텍스쳐의 영역을 획득:
		//		Width와 Height에 Scale벡터를 적용한 뒤에 적용된 두 값의 평균값을 반지름으로 삼는다.
		//		Scale이 적용된 Width와 Height 계산:
		//			Scale 매트릭스는 x의 scale 요소(Sx)가 1행 1열, y의 scale 요소(Sy)는 2행 2열 식으로
		//			나열되어 있으므로 이 값만을 이용할 것이다.
		BOOL is_hit = 0;
		D3DXIntersect(sub.getBall(), &(ray.center), &ray.direction, &is_hit, 0, 0, 0, 0, 0 ,0);
		return is_hit == 1;
	}

	bool Picker::_isPicked( Camera& camera )
	{
		POINT cursor = _computeScreenCursorPosition();

		PerspectiveCamera& cam = (PerspectiveCamera&) camera;
		PerspectiveCamera::Connector& c = cam.getConnector();
		type_int	x = 0, y = 0, width = 0, height = 0;
		if( ! c.getIsViewportMaxmized().getValue())
		{
			x = c.getViewPortX().getValue(),
			y = c.getViewPortY().getValue(),
			width = c.getViewPortWidth().getValue(),
			height = c.getViewPortHeight().getValue();
		}
		else
		{
			D3DVIEWPORT9& viewportcam = cam.createMaxmizedViewPort();
			x = viewportcam.X,
			y = viewportcam.Y,
			width = viewportcam.Width,
			height = viewportcam.Height;			
		}
		
		if(	x < cursor.x && cursor.x < x + width	&&
			y < cursor.y && cursor.y < y + height	)
			return true;

		return false;
	}

	int Picker::_isRayIntersected(RayGenerator::Ray& ray, HierarchyMeshX& mesh, D3DXFRAME& frame)
	{
		if( ! &frame) return 2;
		if(	frame.pMeshContainer					&&
			frame.pMeshContainer->MeshData.pMesh	)
		{
			BOOL is_hit = 0;
			D3DXIntersect(frame.pMeshContainer->MeshData.pMesh, &(ray.center), &ray.direction, &is_hit, 0, 0, 0, 0, 0 ,0);
			return is_hit;
		}

		if(frame.pFrameSibling)
		{
			int result = _isRayIntersected(ray, mesh, *frame.pFrameSibling);
			if(result != 2)
				return result;
		}
		if(frame.pFrameFirstChild)
		{
			int result = _isRayIntersected(ray, mesh, *frame.pFrameFirstChild);
			if(result != 2)
				return result;
		}

		return 2;
	}

	type_result Picker::execute()
	{
		NEKeyCodeSet& keyset = getKeySet();
		NEModuleSelector& selector = static_cast<NEModuleSelector&>(keyset[1]);
		Camera& camera = _castCamera();
		if( ! &camera)
		{
			ALERT_ERROR(" : 카메라가 없음");
			return false;
		}
		Window& window = getDependent();
		if( ! &window)
		{
			ALERT_ERROR(" : 윈도우가 없음");
			return RESULT_TYPE_ERROR;
		}
		Referer* nullpointer = NE_NULL;
		Referer::setGlobalHoveredReferer(*nullpointer);
		const MSG& msg = window.getMSG();		
		if(msg.message == WM_LBUTTONDOWN)
			_depickCameras();
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		static type_code referer_code = moduler.getModule(Referer().getHeader()).getScriptCode();
		static type_code hierarchy_code = moduler.getModule(HierarchyReferer().getHeader()).getScriptCode();
		static type_code sub_code = moduler.getModule(HierarchySubReferer().getHeader()).getScriptCode();
		static type_code camera_code = moduler.getModule(PerspectiveCamera().getHeader()).getScriptCode();
		static type_code pages_code = moduler.getModule(Pages().getHeader()).getScriptCode();
		static type_code sprite_referer = moduler.getModule(SpriteReferer().getHeader()).getScriptCode();

		//	main:
		//		
		//		타겟팅:
		//			일단 카메라를 제외한 리소스들을 먼저 체킹한다:
		bool is_picking_refreshed = false;
		bool is_second_trigger = false;
		while( & selector.getModule())
		{
			if( ! selector.peekNode().isEnable()	||
				! selector.peekModule().isEnable()	) 
				continue;

			NEModule& module = selector.peekModule();
			if(	module.getScriptCode() != referer_code		&&
				module.getScriptCode() != hierarchy_code	&&
				module.getScriptCode() != sub_code			&&
				module.getScriptCode() != sprite_referer	)
				continue;

			bool result = false;
			Referer* referer = 0x00;
			referer = static_cast<Referer*>(&module);			
			if( result = _isPicked(*referer, camera))
			{
				Referer::setGlobalHoveredReferer(*referer);
				if(_on_picked_handler && referer)
					getOnPickedHandler().onHovered(module);
			}

			if(result)
			{
				switch(msg.message)
				{
				case WM_LBUTTONDOWN:
					is_picking_refreshed = true;
					Referer::setGlobalReferer(*referer);
					if(_on_picked_handler && referer)
					{
						getOnPickedHandler().onLeftButtonClickedDown(module, is_second_trigger);
						is_second_trigger = !is_second_trigger;
					}
					break;

				case WM_LBUTTONUP:
					{
						type_result result = _transiteReferer(Referer::getGlobalHoveredReferer(), Referer::getGlobalReferer());
						if(NEResult::hasError(result))
						{
							ALERT_ERROR(" : 이동 중에 에러 발생!");
							return result;
						}

						if(_on_picked_handler && referer)
						{
							getOnPickedHandler().onLeftButtonClickedUp(module, is_second_trigger);
							is_second_trigger = !is_second_trigger;
						}
					}
					break;

				case WM_LBUTTONDBLCLK:
					if(_on_picked_handler && referer)
					{
						getOnPickedHandler().onLeftButtonDoubleClicked(module, is_second_trigger);
						is_second_trigger = !is_second_trigger;
					}

					break;

				case WM_RBUTTONUP:
					if(_on_picked_handler && referer)
					{
						getOnPickedHandler().onRightButtonClickedUp(module, is_second_trigger);
						is_second_trigger = !is_second_trigger;
					}
					break;

				case WM_RBUTTONDOWN:
					if(_on_picked_handler && referer)
					{
						getOnPickedHandler().onRightButtonClickedDown(module, is_second_trigger);
						is_second_trigger = !is_second_trigger;
					}
					break;

				case WM_RBUTTONDBLCLK:
					if(_on_picked_handler && referer)
					{
						getOnPickedHandler().onRightButtonDoubleClicked(module, is_second_trigger);
						is_second_trigger = !is_second_trigger;
					}
					break;				
				}
			}
		}

		//	post:
		//		클릭을 했는데도 불구하고 리소스를 캐치하지 못했다?
		//		그러면 카메라를 캐치한다.
		if(msg.message == WM_LBUTTONDOWN && ! is_picking_refreshed)
		{
			Referer::setGlobalReferer(*nullpointer);
			selector.initializeReferingPoint();
			while( & selector.getModule())
			{
				if( ! selector.peekNode().isEnable()	||
					! selector.peekModule().isEnable()	) 
					continue;

				NEModule& module = selector.peekModule();
				if(module.getScriptCode() != pages_code)
					continue;

				Pages& casted = static_cast<Pages&>(module);				
				NEModuleCodeSet& ms = casted.getConnector().getPages().getValue();
				type_index page_index = casted.getConnector().getPageIndex().getValue();
				
				if(page_index < 0 || page_index > ms.getLengthLastIndex())
					continue;
				
				NEKeyCodeSet& ks = ms[page_index].getKeySet();
				if(ks[0].isSubClassOf(NEType::NEMODULE_CODESET_KEY))
				{
					NEModuleCodeSet& ms1 = ((NEModuleCodeSetKey&) ks[0]).getValue();
					for(int n2=0; n2 < ms1.getLength() ;n2++)
					{
						if(ms1[n2].getScriptCode() != camera_code)
							continue;							
						PerspectiveCamera& cam = (PerspectiveCamera&) ms1[n2];
						if(cam.getConnector().getIsViewportMaxmized().getValue())
							continue;
						if(_isPicked(cam))
						{
							_depickCameras();
							cam.is_picked = true;

							switch(msg.message)
							{
							case WM_LBUTTONDOWN:
								if(_on_picked_handler)
								{
									getOnPickedHandler().onLeftButtonClickedDown(cam, is_second_trigger);
									is_second_trigger = !is_second_trigger;
								}
								break;

							case WM_LBUTTONUP:
								if(_on_picked_handler)
								{
									getOnPickedHandler().onLeftButtonClickedUp(cam, is_second_trigger);
									is_second_trigger = !is_second_trigger;
								}
								break;

							case WM_LBUTTONDBLCLK:
								if(_on_picked_handler)
								{
									getOnPickedHandler().onLeftButtonDoubleClicked(cam, is_second_trigger);
									is_second_trigger = !is_second_trigger;
								}

								break;

							case WM_RBUTTONUP:
								if(_on_picked_handler)
								{
									getOnPickedHandler().onRightButtonClickedUp(cam, is_second_trigger);
									is_second_trigger = !is_second_trigger;
								}
								break;

							case WM_RBUTTONDOWN:
								if(_on_picked_handler)
								{
									getOnPickedHandler().onRightButtonClickedDown(cam, is_second_trigger);
									is_second_trigger = !is_second_trigger;
								}
								break;

							case WM_RBUTTONDBLCLK:
								if(_on_picked_handler)
								{
									getOnPickedHandler().onRightButtonDoubleClicked(cam, is_second_trigger);
									is_second_trigger = !is_second_trigger;
								}
								break;				
							}
						}
					}
				}

			}
		}		
		return RESULT_SUCCESS | RESULT_FALSE;
	}

	type_result Picker::_transiteReferer(Referer& destination, Referer& origin)
	{
		//	origin는 모듈이므로, 이를 소유하고 있는 건 ModuleKeyCodeSet 이나, Node의
		//	ModuleSet이다. 본래라면 ModuleKeyCodeSet도 조사를 해야하나, 여기서는, 
		//	Referer만 찾는다.
		if(	! &origin				|| 
			! &destination			||
			&origin == &destination	) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		static NECodeSet codeset;
		static type_code referer_code = Kernal::getInstance().getModuleManager().getModule(Referer().getHeader()).getScriptCode();
		static type_code sub_code = Kernal::getInstance().getModuleManager().getModule(HierarchySubReferer().getHeader()).getScriptCode();
		if(origin.getScriptCode() == sub_code) return RESULT_TYPE_ERROR;
		if(codeset.getLength() == 0)
		{
			codeset.create(2);
			codeset.push(referer_code);
			codeset.push(sub_code);
		}
		NEModuleSelector selector;
		selector.setNodeType(NECodeType::ALL);
		selector.setModuleType(NECodeType::SCRIPT);
		selector.setModuleCodeSet(codeset);

		//	노드 밑에 있는 경우:
		while( &selector.getNode())
		{
			NEModuleCodeSet& moduleset = selector.peekNode().getModuleSet();
			for(int n=0; n < moduleset.getLength() ;n++)
				if(moduleset[n].getScriptCode() == referer_code)
				{
					Referer& casted = static_cast<Referer&>(moduleset[n]);
					if(&casted == &origin)
						return _transite(destination, origin, moduleset, n);
				}
		}
		//	레퍼러 밑에 서브인 경우:
		selector.initializeReferingPoint();
		while( &selector.getModule())
		{
			Referer& referer = static_cast<Referer&>(selector.peekModule());
			NEModuleCodeSet& moduleset = referer.getConnector().getModuleCodeSetKey().getValue();
			for(int n=0; n < moduleset.getLength() ;n++)
				if(	moduleset[n].getScriptCode() == referer_code	||
					moduleset[n].getScriptCode() == sub_code		)
				{
					Referer& casted = static_cast<Referer&>(moduleset[n]);
					if(&casted == &origin)
						return _transite(destination, origin, moduleset, n);
				}
			
		}

		return RESULT_TYPE_ERROR;
	}

	type_result Picker::_transite( Referer& destination, Referer& origin, NEModuleCodeSet& origin_owner, type_index index)
	{
		if(origin_owner.getLengthLastIndex() < index)
		{
			ALERT_ERROR(" : 인덱스가 적어서 에러!");
			return RESULT_TYPE_ERROR;
		}


		//	복사하고 삭제한다:
		//		스케일값 조정:
		//			복사될 곳의 스케일 추출:
		float destination_scale = D3DXVec3Length(&D3DXVECTOR3(destination.getWorldMatrix()._11, destination.getWorldMatrix()._21, destination.getWorldMatrix()._31));
		//			자신의 스케일 추출:
		float my_scale = D3DXVec3Length(&D3DXVECTOR3(origin.getWorldMatrix()._11, origin.getWorldMatrix()._12, origin.getWorldMatrix()._13));
		//			보정치 획득:
		//				내 최종 월드 스케일 = 타겟의 최종 월드 스케일 이므로,
		//				보정된 my_scale * my_parent_scale * my_scale = destination_world_scale
		//				보정치 = my_world_scale / destination_world_scale
		float adjustment = my_scale / destination_scale;
		//			자신의 스케일을 보정치 적용:
		D3DXMatrixScaling(&origin.getScaleMatrix(), adjustment, adjustment, adjustment);
		//		인스턴스 이동:
		NEModuleCodeSet& moduleset = destination.getConnector().getModuleCodeSetKey().getValue();
		if(moduleset.getLength() == moduleset.getSize())
			moduleset.resize(moduleset.getLength() + 1);
		moduleset.push(origin);
		origin_owner.remove(index);

		return RESULT_SUCCESS;
	}

	void Picker::_depickCameras()
	{
		NEModuleSelector ms;
		ms.setNodeType(NECodeType::ALL);
		NECodeSet c(1);
		static type_code camera = Kernal::getInstance().getModuleManager().getModule(PerspectiveCamera().getHeader())
			.getScriptCode();
		c.push(camera);
		ms.setModuleType(NECodeType::SCRIPT);
		ms.setModuleCodeSet(c);

		NEModule* m = 0;
		while(m = &ms.getModule())
		{
			PerspectiveCamera& cam = (PerspectiveCamera&) ms.peekModule();

			cam.is_picked = false;
		}
	}

}