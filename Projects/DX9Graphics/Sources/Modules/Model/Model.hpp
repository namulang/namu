#pragma once

#include "../Particle/Particle.hpp"
#include <stdlib.h>

namespace DX9Graphics
{
	class SpriteTexter;
	class Modeling;
	class Texture;
	class Sprite;

	class NE_DLL Model : public Particle
	{
	public:
		typedef Model ThisClass;
		typedef Particle SuperClass;
		typedef type_result (ThisClass::*onSearched)(NEModule&);

	public:
		NETArgument<NEModuleSelector>	arg_modeling_binder;
		NETArgument<NEModuleSelector>	arg_texture_binder;
		NETArgument<NEModuleSelector>	arg_texter_binder;
		NETArgument<NENodeCodeSetKey>	arg_children;

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			SuperClass::_onFetchArguments(tray);

			tray.push(arg_modeling_binder);
			tray.push(arg_texture_binder);
			tray.push(arg_texter_binder);
			tray.push(arg_children);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchModule()
		{
			SuperClass::_onFetchModule();

			arg_modeling_binder.getValue().NENodeSelector::isUsingAutoBinding() = true;
			arg_modeling_binder.getValue().isUsingAutoBinding() = true;
			arg_texture_binder.getValue().NENodeSelector::isUsingAutoBinding() = true;
			arg_texture_binder.getValue().isUsingAutoBinding() = true;
			arg_texter_binder.getValue().NENodeSelector::isUsingAutoBinding() = true;
			arg_texter_binder.getValue().isUsingAutoBinding() = true;
			arg_texter_binder.setEnable(false);

			return RESULT_SUCCESS;
		}
		virtual type_result _onExecute();


	public:
		Model()
			: SuperClass()
		{
			_release();
		}
		Model(const Model& source)
			: SuperClass(source)
		{
			_assign(source);
		}

	public:				
		Texture& getTexture();
		Sprite& getModeling();
		SpriteTexter& getTexter();
		const D3DXMATRIX& getModelMatrix() const { return _model; }
		D3DXMATRIX& getModelMatrix() { return _model; }
		const D3DXMATRIX& getWorldMatrix() const { return _world; }
		D3DXMATRIX& getWorldMatrix() { return _world; }
		const D3DXMATRIX& getParentWorldMatrix() const {return _parent_world; }
		D3DXMATRIX& getParentWorldMatrix() { return _parent_world; }

	public:
		const ThisClass& operator=(const ThisClass& source)
		{
			if(this == &source) return *this;

			SuperClass::operator=(source);

			return _assign(source);
		}
		bool operator==(const ThisClass& source) const
		{
			if(SuperClass::operator!=(source)) return false;
			if(_parent_world != source._parent_world) return false;
			if(_world != source._world) return false;
			if(_model != source._model) return false;

			return true;
		}
		bool operator!=(const ThisClass& source) const
		{
			return ! ThisClass::operator==(source);
		}

	public:
		virtual type_result render();		

		virtual void release()
		{
			SuperClass::release();

			_release();
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
		{
			SuperClass::serialize(saver);

			saver.execute((char*) &_model, sizeof(D3DXMATRIX));
			saver.execute((char*) &_parent_world, sizeof(D3DXMATRIX));
			saver.execute((char*) &_world, sizeof(D3DXMATRIX));

			return saver;
		}
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
		{
			SuperClass::serialize(loader);

			loader.execute((char*) &_model, sizeof(D3DXMATRIX));
			loader.execute((char*) &_parent_world, sizeof(D3DXMATRIX));
			loader.execute((char*) &_world, sizeof(D3DXMATRIX));

			return loader;			
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	private:
		type_result _executeChildren()
		{
			NENodeCodeSet& nodeset = arg_children.getValue();

			for(int n=0; n < nodeset.getSize(); n++)
			{
				NENode& node = nodeset[n];

				_getGlobalParentWorld() = _world;
				node.execute();
			}

			return RESULT_SUCCESS;
		}
		type_result _updateModelMatrix()
		{
			_model = createScalingMatrix() * createRotationMatrix() * createTranslationMatrix();

			return RESULT_SUCCESS;
		}
		type_result _updateWorldMatrix()
		{
			_world = _model * _parent_world;

			return RESULT_SUCCESS;
		}		

		void _release()
		{
			D3DXMATRIX i;
			D3DXMatrixIdentity(&i);

			_world = _parent_world = _model = i;
		}
		const ThisClass& _assign(const ThisClass& source)
		{
			if(this == &source) return *this;

			_model = source._model;
			_world= source._world;
			_parent_world = source._parent_world;
			arg_children = source.arg_children;
			arg_modeling_binder = source.arg_modeling_binder;
			arg_texture_binder = source.arg_texture_binder;
			arg_texter_binder = source.arg_texter_binder;

			return *this;
		}

		type_result _updateRenderState();

	private:
		D3DXMATRIX _model;
		D3DXMATRIX _world;
		D3DXMATRIX _parent_world;

	public:
		static const NECodeSet& getModuleScriptCodes();

	private:
		static D3DXMATRIX& _getGlobalParentWorld()
		{
			static D3DXMATRIX _instance;
			static bool _is_first = true;
			if(_is_first)
			{
				D3DXMatrixIdentity(&_instance);
				_is_first = false;
			}

			return _instance;
		}
	};
}