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
		NETArgument<NEFloatKey>	arg_bounding_sphere_radius;

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_bounding_sphere_radius);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchModule()
		{
			return arg_bounding_sphere_radius.setPurposeLimitation(NEArgumentBase::READ_BY);			
		}

	public:
		Sprite()
			: SuperClass(), _sprite(0)
		{

		}
		~Sprite()
		{
			ThisClass::releaseResource();
		}

	public:
		LPD3DXSPRITE getSprite() { return _sprite; }
		const LPD3DXSPRITE getSprite() const { return _sprite; }

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
		virtual const NEExportable::ModuleHeader& getHeader() const;
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
		type_result _renderSprite(const Model& model, Texture& texture, LPDIRECT3DDEVICE9 device);
		type_result _adjustUVsBy(const TabledTexture& tabled);

	private:
		LPD3DXSPRITE _sprite;

	public:
		static const NECodeSet& getModuleScriptCodes()
		{
			NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
			NECodeType type(NECodeType::MODULE_SCRIPT);
			static NECodeSet codeset(type);
			if (codeset.getLength() <= 0)
			{				
				codeset.create(1);
				codeset.push(NEExportable::Identifier("Sprite"));
			}

			return codeset;
		}
	};
}