#pragma once

#include "../DockableResource/DockableResource.hpp"

namespace DX9Graphics
{
	class Texture;
	class TabledTexture;

	class NE_DLL Sprite : public DockableResource
	{
	public:
		typedef Sprite ThisClass;
		typedef DockableResource SuperClass;

	public:
		NETArgument<NEFloatKey>		arg_bounding_sphere_radius;
		NETArgument<NEBooleanKey>	arg_render_bounding_sphere;

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_bounding_sphere_radius);
			tray.push(arg_render_bounding_sphere);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchModule()
		{
			arg_render_bounding_sphere.setEnable(false);
			arg_render_bounding_sphere.setValue(false);
			arg_render_bounding_sphere.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_bounding_sphere_radius.setEnable(false);
			arg_bounding_sphere_radius.setValue(1.0f);
			return arg_bounding_sphere_radius.setPurposeLimitation(NEArgumentBase::READ_BY);			
		}

	public:
		Sprite()
			: SuperClass(), _sprite(0), _mesh(0)
		{

		}
		Sprite(const ThisClass& rhs)
			: SuperClass(rhs), _sprite(0), _mesh(0)
		{
			_assign(rhs);
		}
		~Sprite()
		{
			ThisClass::releaseResource();
		}

	public:
		LPDIRECT3DVERTEXBUFFER9 getSprite() { return _sprite; }
		const LPDIRECT3DVERTEXBUFFER9 getSprite() const { return _sprite; }

	public:
		virtual type_result dock(Model& model);
		virtual type_result initializeResource()
		{
			_initializeSprite();

			return SuperClass::initializeResource();
		}
		virtual type_result releaseResource()
		{
			if (_sprite)
				_sprite->Release();
			_sprite = 0;

			return SuperClass::releaseResource();
		}
		virtual type_result execute()
		{
			if (!_sprite)
				initializeResource();

			return RESULT_SUCCESS;
		}
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if(_header.isValid() != RESULT_NOTHING)
			{
				_header.getName()		= "Sprite";
				_header.getDeveloper()	= "kniz";
				_header.setRevision(1);
				_header.getComment() = 
					"3D공간에 그림(Texture)가 놓여질 사각형 평면입니다.\n충돌검사때 사용될 BoundingSphere의 반지름을 지정할 수 있습니다.(자동으로 계산되지 않습니다)";
				_header.getVersion() = "0.0.1a";
				_header.getReleaseDate() = "2013-08-10";

				NETStringSet& args = _header.getArgumentsComments();
				args.resize(2);
				args.push("BoundingSphere Radius\n충돌검사때 사용될 가상의 구의 반지름입니다. 크면 클수록 충돌 여부가 민감해집니다.");
				args.push("BoundingSphere 출력\n지정한 Radius를 가진 가상 충돌 구(sphere)를 디버깅을 위해 화면에 그립니다.");
			}

			return _header;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		virtual void release()
		{
			SuperClass::release();

			ThisClass::releaseResource();
		}

	private:
		type_result _initializeSprite();
		void _renderSphere(LPDIRECT3DDEVICE9 device, const D3DXMATRIX& world)
		{
			if(	! arg_render_bounding_sphere.isEnable() ||
				! arg_render_bounding_sphere.getValue()	||
				! _readySphere(device)					||
				! _mesh									)
				return;

			device->SetTransform(D3DTS_WORLD, &world);
			DWORD original = 0;
			device->GetRenderState(D3DRS_FILLMODE, &original);
			device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

			device->SetTexture(0, 0);
			_mesh->DrawSubset(0);

			device->SetRenderState(D3DRS_FILLMODE, original);

		}
		type_result _renderSprite(Model& model, Texture& texture, LPDIRECT3DDEVICE9 device);
		type_bool _readySphere(LPDIRECT3DDEVICE9 device)
		{
			if( ! arg_bounding_sphere_radius.isEnable()		||
				arg_bounding_sphere_radius.getValue() <= 0	)
				return false;

			if(_radius != arg_bounding_sphere_radius.getValue())
			{
				_radius = arg_bounding_sphere_radius.getValue();

				D3DXCreateSphere(device, _radius, 10, 10, &_mesh, 0x00);
			}

			return true;
		}
		ThisClass& _assign(const ThisClass& source)
		{
			if (this == &source) return *this;

			arg_bounding_sphere_radius = source.arg_bounding_sphere_radius;
			arg_render_bounding_sphere = source.arg_render_bounding_sphere;

			return *this;
		}

	private:
		LPDIRECT3DVERTEXBUFFER9 _sprite;
		LPD3DXMESH _mesh;
		type_float _radius;

	public:
		static const NECodeSet& getModuleScriptCodes()
		{
			NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
			NECodeType type(NECodeType::MODULE_SCRIPT);
			static NECodeSet codeset(type);
			if (codeset.getLength() <= 0)
			{				
				codeset.create(1);
				codeset.push(NEExportable::Identifier("Sprite.kniz"));
			}

			return codeset;
		}
		static D3DXMATRIX adj;
		static D3DXMATRIX adj_for_font;
	};
}