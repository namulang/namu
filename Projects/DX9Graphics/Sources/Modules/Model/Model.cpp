#include "Model.hpp"
#include "define.hpp"
#include "../DX9/DX9.hpp"
#include "../Sprite/Sprite.hpp"
#include "../Texture/Texture.hpp"
#include "../TabledTexture/TabledTexture.hpp"
#include "../SpriteTexter/SpriteTexter.hpp"
#include "../AnimatedModel/AnimatedModel.hpp"

namespace DX9Graphics
{
	const NEExportable::ModuleHeader& Model::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T(_NAME);
			_header.getDeveloper() = _T(_DEVELOPER);
			_header.setRevision(_REVISION);
			_header.getComment() = _T(_COMMENT);
			_header.getVersion()  = _T(_VERSION);
			_header.getReleaseDate() = _T(_DATE);
			_header.getModuleDependencies().create(0);
			_header.setMaxErrorCodeCount(1);
		}

		return _header;
	}

	type_result Model::_bindModelingModule()
	{
		//	main:
		const NECodeSet& codeset = Sprite::getSpriteCodeSet();		
		NEModuleSelector& selector = getModelingSelector();
		//		Identifier 획득:
		while( &selector.getModule())
		{
			NEModule& module = selector.peekModule();
			if(codeset.find(module.getScriptCode()) != NE_INDEX_ERROR)
			{
				selector.bind();
				selector.initializeReferingPoint();
				return RESULT_SUCCESS;
			}
		}


		//	post:
		ALERT_ERROR(" : 모듈 셀렉터로부터 메시를 찾지 못했습니다.");
		return RESULT_TYPE_ERROR;
	}

	type_result Model::render()
	{
		if( ! isEnable()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		if( ! isRenderable()) return RESULT_SUCCESS;
		if( ! getModelingSelector().getBinder().isBinded())
		{
			ALERT_WARNING(" : 모델링 바인딩 실패로중지");
			return RESULT_SUCCESS;
		}
		if( ! getTextureSelector().getBinder().isBinded())
		{
			ALERT_WARNING(" : 텍스쳐 바인딩 실패로 중지");
			return RESULT_TYPE_ERROR;
		}

		DockableResource& modeling = static_cast<DockableResource&>(getModelingSelector().getBinder().getBinded()),
						& texture = static_cast<DockableResource&>(getTextureSelector().getBinder().getBinded());

		texture.dock(*this);
		_updateRenderState();
		return modeling.dock(*this);
	}

	type_result Model::_bindTextureModule()
	{
		//	main:
		NECodeSet& codeset = _getTextureCodeSet();		
		NEModuleSelector& selector = getTextureSelector();
		//		Identifier 획득:
		while( &selector.getModule())
		{
			NEModule& module = selector.peekModule();
			if(codeset.find(module.getScriptCode()) != NE_INDEX_ERROR)
			{
				selector.bind();
				return RESULT_SUCCESS;
			}
		}


		//	post:
		ALERT_ERROR(" : 모듈셀렉터로부터리소스를찾지못했습니다.");
		return RESULT_TYPE_ERROR;
	}

	NECodeSet& Model::_getTextureCodeSet()
	{
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		static NECodeSet codeset;
		if(codeset.getLength() <= 0)
		{
			codeset.create(2);
			codeset.setCodeType(NECodeType::SCRIPT);
			codeset.push(Texture().getHeader());
			codeset.push(TabledTexture().getHeader());			
		}

		return codeset;
	}

	const NECodeSet& Model::getScriptCodeSet()
	{
		static NECodeSet instance;
		if(instance.getSize() <= 0)
		{
			NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
			instance.create(2);
			instance.setCodeType(NECodeType::SCRIPT);
			instance.push(Model().getHeader());
			instance.push(AnimatedModel().getHeader());
		}

		return instance;
	}

	type_result Model::_bindTexterModule()
	{
		//	pre:
		if( ! isFontEnabled())	return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		const NECodeSet& cs = SpriteTexter::getScriptCodeSet();
		NEModuleSelector& sel = getTexterSelector();
		//		Identifier 획득:
		while(NEModule* itr = &sel.getModule())
		{
			if(cs.find(itr->getScriptCode()) != NE_INDEX_ERROR)
			{
				sel.bind();
				return RESULT_SUCCESS;
			}
		}


		//	post:
		ALERT_ERROR(" : 모듈셀렉터로부터리소스를찾지못했습니다.");
		return RESULT_TYPE_ERROR;
	}

	type_result Model::_updateRenderState()
	{
		NEModuleSelector& sel = getModelingSelector();
		DX9Binder& binder = (DX9Binder&) sel.getModule();
		sel.initializeReferingPoint();
		DX9* dx9 = &binder ? &binder.getBinded() : 0;
		LPDIRECT3DDEVICE9 dev = dx9 ? dx9->getDevice() : 0;
		if( ! dev)
		{
			ALERT_WARNING("DX9 바인딩 실패로 RenderState 변경 실패");
			return RESULT_TYPE_WARNING;
		}
		
		
		//	main:
		type_byte	src = getSourceBlend(),
					dest = getDestBlend();
		if(src)
			dev->SetRenderState(D3DRS_SRCBLEND, src);
		if(dest)
			dev->SetRenderState(D3DRS_DESTBLEND, dest);

		return RESULT_SUCCESS;
	}
}