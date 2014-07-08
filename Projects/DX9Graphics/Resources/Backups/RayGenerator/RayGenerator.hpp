#pragma once

#include "../WindowDependentModule/WindowDependentModule.hpp"

namespace DX9Graphics
{
	class Mesh;
	class Camera;
	class Referer;
	class RenderableResource;

	class NE_DLL RayGenerator : public WindowDependentModule
	{
		typedef RayGenerator ThisClass;
		typedef WindowDependentModule SuperClass;

	public:
#include "innerclass/Ray/Ray.hpp"
#include "innerclass/Connector/Connector.hpp"

	public:
		ThisClass()
			:SuperClass()
		{
			ZeroMemory(&_first_point, sizeof(POINT));
		}
		ThisClass(const ThisClass& source)
			:SuperClass(source)
		{
			getConnector().connect(getKeySet());
			ZeroMemory(&_first_point, sizeof(POINT));
		}

	public:
		Connector& getConnector() {return _connector;}
		const Connector& getConnector() const {return _connector;}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual type_result initialize()
		{
			SuperClass::initialize();			//	윈도우
			NEKeyCodeSet& keyset = getKeySet();
			keyset.resize(keyset.getLength() + 2);	
			keyset.push(NEModuleSelector());	//	레퍼러
			keyset.push(NEModuleSelector());	//	어떤 카메라가?

			getConnector().connect(keyset);

			return RESULT_SUCCESS;
		}	

	protected:
		POINT _computeScreenCursorPosition();
		Ray _createRayInViewMatrix(Camera& camera);
		void _transformRayToOtherSpace(Ray& ray, const D3DXMATRIX& space)
		{
			D3DXVec3TransformCoord(&ray.center, &ray.center, &space);
			D3DXVec3TransformNormal(&ray.direction, &ray.direction, &space);
			D3DXVec3Normalize(&ray.direction, &ray.direction);
		}
		Camera& _castCamera();
		RenderableResource& _getBindedFromReferer(Referer& referer);

	protected:
		Connector _connector;
		POINT _first_point;
	};
}