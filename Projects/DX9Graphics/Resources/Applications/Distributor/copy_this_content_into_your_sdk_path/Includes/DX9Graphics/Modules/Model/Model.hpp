#pragma once

#include "../Particle/Particle.hpp"
#include <stdlib.h>

namespace DX9Graphics
{
	class NE_DLL Model : public Particle
	{
		typedef Model ThisClass;
		typedef Particle SuperClass;
		typedef type_result (ThisClass::*onSearched)(NEModule&);

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

		virtual ~Model()
		{

		}
	
	public:		
		NENodeCodeSet& getSubParticles()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<NENodeCodeSet&>(consted_this->getSubParticles());
		}
		const NENodeCodeSet& getSubParticles() const
		{
			const NEKey& somekey = getKeySet()[15];
			if( ! somekey.isSubClassOf(NEType::NENODE_CODESET_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 15번키가 NENODECODESET_KEY여야 합니다.");
				const NENodeCodeSet* nullpoint = 0;
				return *nullpoint;
			}

			const NENodeCodeSetKey& target = static_cast<const NENodeCodeSetKey&>(somekey);
			return target.getValue();
		}
		type_bool& isRenderable()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_bool&>(consted_this->isRenderable());
		}
		const type_bool& isRenderable() const
		{
			const NEKey& somekey = getKeySet()[16];
			if( ! somekey.isSubClassOf(NEType::NEBOOLEAN_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 16번키가 NEBOOLEAN_KEY키여야 합니다.");
				const type_bool* nullpoint = 0;
				return *nullpoint;
			}

			return (static_cast<const NEBooleanKey&>(somekey)).getValue();
		}
		NEModuleSelector& getModelingSelector()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<NEModuleSelector&>(consted_this->getModelingSelector());
		}
		const NEModuleSelector& getModelingSelector() const
		{
			const NEKey& somekey = getKeySet()[17];
			if( ! somekey.isSubClassOf(NEType::NEMODULE_SELECTOR))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 17번키가 NEMODULE_SELECTOR키여야 합니다.");
				const NEModuleSelector* nullpoint = 0;
				return *nullpoint;
			}

			const NEModuleSelector& target = static_cast<const NEModuleSelector&>(somekey);
			return target;
		}
		NEModuleSelector& getTextureSelector()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<NEModuleSelector&>(consted_this->getTextureSelector());
		}
		const NEModuleSelector& getTextureSelector() const
		{
			const NEKey& somekey = getKeySet()[18];
			if( ! somekey.isSubClassOf(NEType::NEMODULE_SELECTOR))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 18번키가 NEMODULE_SELECTOR키여야 합니다.");
				const NEModuleSelector* nullpoint = 0;
				return *nullpoint;
			}

			const NEModuleSelector& target = static_cast<const NEModuleSelector&>(somekey);
			return target;
		}
		type_bool& isFontEnabled()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_bool&>(consted_this->isFontEnabled());
		}
		const type_bool& isFontEnabled() const
		{
			const NEKey& somekey = getKeySet()[19];
			if( ! somekey.isSubClassOf(NEType::NEBOOLEAN_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 19번키가 NEBOOLEAN_KEY키여야 합니다.");
				const type_bool* nullpoint = 0;
				return *nullpoint;
			}

			return (static_cast<const NEBooleanKey&>(somekey)).getValue();
		}
		NEModuleSelector& getTexterSelector()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<NEModuleSelector&>(consted_this->getTexterSelector());
		}
		const NEModuleSelector& getTexterSelector() const
		{
			const NEKey& somekey = getKeySet()[20];
			if( ! somekey.isSubClassOf(NEType::NEMODULE_SELECTOR))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 20번키가 NEMODULE_SELECTOR키여야 합니다.");
				const NEModuleSelector* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEModuleSelector&>(somekey);
		}
		const D3DXMATRIX& getModelMatrix() const { return _model; }
		D3DXMATRIX& getModelMatrix() { return _model; }
		const D3DXMATRIX& getWorldMatrix() const { return _world; }
		D3DXMATRIX& getWorldMatrix() { return _world; }
		const D3DXMATRIX& getParentWorldMatrix() const {return _parent_world; }
		D3DXMATRIX& getParentWorldMatrix() { return _parent_world; }
		NEModuleBinder& getTextureBinder() { return _texture_binder; }
		const NEModuleBinder& getTextureBinder() const { return _texture_binder; }
		NEModuleBinder& getModelingBinder() { return _modeling_binder; }
		const NEModuleBinder& getModelingBinder() const { return _modeling_binder; }
		NEModuleBinder& getTexterBinder() { return _texter_binder; }
		const NEModuleBinder& getTexterBinder() const { return _texter_binder; }

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
		virtual type_result initialize()
		{
			SuperClass::initialize();
			_release();

			NEKeyCodeSet& keyset = getKeySet();
			keyset.resize(keyset.getLength() + 6);
			keyset.push(NENodeCodeSetKey());	//	14:	SubParticles
			keyset.push(NEBooleanKey(1));		//	15:	렌더링하는가?
			keyset.push(NEModuleSelector());	//	16:	Modeling 모듈
			keyset.push(NEModuleSelector());	//	17:	Texture 모듈
			keyset.push(NEBooleanKey(0));		//	18:	텍스트 기능을 사용할 것인가?
			keyset.push(NEModuleSelector());	//	19: 텍스터
			
			return RESULT_SUCCESS;
		}
		virtual type_result execute()
		{	
			//	pre:			
			if( ! isEnable()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
			type_bool is_renderable = isRenderable();
			if( is_renderable				&&
				! _texture_binder.isBinded())
				_bindTextureModule();
			if(is_renderable				&&
				! _modeling_binder.isBinded())
				_bindModelingModule();
			if( is_renderable				&&
				isFontEnabled()				&& 
				! _texter_binder.isBinded()	)
				_bindTexterModule();
			

			//	main:
			//		ParentWorldMatrix 할당받기:
			_parent_world = _getGlobalParentWorld();
			_updateModelMatrix();
			_updateWorldMatrix();


			//	post:
			//		자식 모듈셋 실행:
			_executeChildren();
			_getGlobalParentWorld() = _parent_world;
			return RESULT_SUCCESS;
		}
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
			NENodeCodeSet& nodeset = getSubParticles();

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

			return *this;
		}
		NECodeSet& _getModelingCodeSet();
		type_result _bindModelingModule();
		type_result _bindTextureModule();
		type_result _bindTexterModule();
		NECodeSet& _getTextureCodeSet();
		type_result _updateRenderState();

	private:
		D3DXMATRIX _model;
		D3DXMATRIX _world;
		D3DXMATRIX _parent_world;
		NEModuleBinder _modeling_binder;
		NEModuleBinder _texture_binder;
		NEModuleBinder _texter_binder;

	public:
		static const NECodeSet& getModelCodeSet();

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