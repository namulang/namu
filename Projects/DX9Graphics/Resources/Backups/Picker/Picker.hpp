#pragma once

#include "../RayGenerator/RayGenerator.hpp"

namespace DX9Graphics
{
	class Mesh;
	class Camera;
	class Referer;
	class Sprite;
	class HierarchyMeshX;
	class HierarchySubReferer;

	class NE_DLL Picker : public RayGenerator
	{
		typedef Picker ThisClass;
		typedef RayGenerator SuperClass;

	public:
		Picker()
			:SuperClass()
		{
			_on_picked_handler = 0x00;
		}

	public:
		class NE_DLL OnPickedHandler
		{
		public:
			virtual void onLeftButtonClickedDown(NEModule& module, bool is_second_trigger)
			{
				
			}
			virtual void onLeftButtonDoubleClicked(NEModule& module, bool is_second_trigger)
			{
				
			}
			virtual void onLeftButtonClickedUp(NEModule& module, bool is_second_trigger)
			{

			}
			virtual void onRightButtonClickedDown(NEModule& module, bool is_second_trigger)
			{

			}
			virtual void onRightButtonDoubleClicked(NEModule& module, bool is_second_trigger)
			{

			}
			virtual void onRightButtonClickedUp(NEModule& module, bool is_second_trigger)
			{

			}
			virtual void onHovered(NEModule& module)
			{

			}
		};

	public:
		OnPickedHandler& getOnPickedHandler() { return *_on_picked_handler;}
		void setOnPickedHandler(OnPickedHandler& new_handler) { _on_picked_handler = &new_handler; }

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual type_result execute();

	public:
		virtual NEObject& clone() const
		{
			return *(new Picker(*this));
		}

	private:		
		bool _isPicked(NEModule& module, Camera& camera);
		bool _isPicked(Camera& camera);
		bool _isPicked(Referer& sprite, Camera& camera);
		bool _isPicked(HierarchySubReferer& sub, SuperClass::Ray& ray);
		void _depickCameras();
		bool _isRayIntersected(SuperClass::Ray& ray, Mesh& mesh);
		bool _isRayIntersected(SuperClass::Ray& ray, Referer& referer, Sprite& sprite);
		int _isRayIntersected(SuperClass::Ray& ray, HierarchyMeshX& referer, D3DXFRAME& frame);
		type_result _transiteReferer(Referer& destination, Referer& origin);
		type_result _transite(Referer& destination, Referer& origin, NEModuleCodeSet& origin_owner, type_index index);
		float _extractScaleX(D3DXMATRIX& world);
		float _extractScaleY(D3DXMATRIX& world);

	private:
		OnPickedHandler* _on_picked_handler;
	};
}