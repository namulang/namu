#include "Model.hpp"
#include "../DX9/DX9.hpp"
#include "../Sprite/Sprite.hpp"
#include "../Texture/Texture.hpp"
#include "../TabledTexture/TabledTexture.hpp"
#include "../SpriteTexter/SpriteTexter.hpp"
#include "../AnimatedModel/AnimatedModel.hpp"

namespace DX9Graphics
{
	SpriteTexter& Model::getTexter()
	{
		return DX9::cast<SpriteTexter>(arg_texter_binder);
	}
	Texture& Model::getTexture()
	{
		return DX9::cast<Texture>(arg_texture_binder);
	}
	Sprite& Model::getModeling()
	{
		return DX9::cast<Sprite>(arg_modeling_binder);
	}
	type_result Model::_onExecute()
	{
		//	pre:			
		if(!isEnable()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;


		//	main:
		//		ParentWorldMatrix 할당받기:
		_updateModelMatrix();
		_updateWorldMatrix();


		//	post:
		//		자식 모듈셋 실행:
		_updateChildren();		
		return RESULT_SUCCESS;
	}

	const NEExportable::ModuleHeader& Model::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName()		= "Model";
			_header.getDeveloper()	= "kniz";
			_header.setRevision(1);
			_header.getComment() = "3차원 공간에 바인딩한 Resource들을 상대 정보로써 표현하는 모듈입니다.\n평면 그림을 나타내는 텍스쳐를 물체를 나타내는 모델링에 씌워서 지정한 좌표와 방향, 크기로 출력합니다.";
			_header.getVersion() = "0.0.1a";
			_header.getReleaseDate() = "2013-08-08";

			NETStringSet& args = _header.getArgumentsComments();
			args = SuperClass::getHeader().getArgumentsComments();
			args.resize(args.getLength() + 4);
			args.push("Modeling\nSprite와 같은 모델링 모듈을 참조합니다.");
			args.push("Texture\nSprite에 매핑해 그릴 텍스쳐 모듈을 참조합니다.");
			args.push("Texter\nSprite를 그릴때 씌여질 문자정보를 저장한 SpriteTexter 모듈를 참조합니다.");
			args.push("Children\n하위 계층구조 모델입니다.\n자식 모델은 부모 모델의 좌표,회전,크기를 원점으로 계산하는 상대값 입니다.");
		}

		return _header;
	}

	type_result Model::render()
	{
		SuperClass::render();

		if( ! isEnable()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;		
		if( ! arg_modeling_binder.isEnable()||
			! arg_texture_binder.isEnable()	) 
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		DockableResource& modeling = DX9::cast<DockableResource>(arg_modeling_binder);
		Texture& texture = DX9::cast<Texture>(arg_texture_binder);	
		if( ! &texture)
			return ALERT_ERROR("주어진 텍스쳐가 없습니다.");

		texture.dock(*this);

		return modeling.dock(*this);
	}

	const NECodeSet& Model::getModuleScriptCodes()
	{
		NECodeType type(NECodeType::MODULE_SCRIPT);
		static NECodeSet instance(type);

		if(instance.getSize() <= 0)
		{
			instance.create(1);
			instance.push(NEExportable::Identifier("AnimatedModel.kniz"));
		}

		return instance;
	}
}