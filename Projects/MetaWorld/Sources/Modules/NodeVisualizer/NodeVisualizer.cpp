#include "NodeVisualizer.hpp"
#include "../PanelBinder/PanelBinder.hpp"
#include "../NodeBinder/NodeBinder.hpp"
#include "../KeyBinder/KeyBinder.hpp"

namespace MetaWorld
{

	NENode& NodeVisualizer::_createAvartar(type_int length)
	{
		NENodeManager& noder = Kernal::getInstance().getNodeManager();	
		const NENode& source = _getSourceAvatarOf(getAvartarWhenSourceIsMostAncestor());

		NENode& avartar = noder.getRootNodes()[noder.getRootNodes().push(source)];	//	IndexedArrayTemplate::push/insert는 retVal로 삽입된 index를 반환한다.
		_onAvatarPushed(avartar, length);
		return avartar;
	}

	NENode& NodeVisualizer::_createAvartar(const NENode& source, NENode& parent_of_avartar, type_int index_between_siblings)
	{
		typedef DX9Graphics::Model Model;
		Model& connection = _searchIn<DX9Graphics::Model>(parent_of_avartar);
		if( ! &connection) 
		{	
			ALERT_ERROR("parent_of_avartar에 DX9Graphics::Model 클래스가 없다.");
			__asm int 3;
		}
		NENode& avatar_source = _getSourceAvatarOf(getAvartarWhenSourceIsNode());
		NENodeCodeSet& ns = connection.getSubParticles();
		
		//	post:
		NENode& avatar = ns[ns.push(avatar_source)];
		_onAvatarPushed(avatar, source, index_between_siblings);
		return avatar;
	}

	NENode& NodeVisualizer::_createAvartar(const NEModule& source, NENode& parent_of_avartar, type_int index_between_siblings)
	{
		typedef DX9Graphics::Model Model;
		Model& connection = _searchIn<DX9Graphics::Model>(parent_of_avartar);
		if( ! &connection) 
		{	
			ALERT_ERROR("parent_of_avartar에 DX9Graphics::Model 클래스가 없다.");
			__asm int 3;
		}
		NENode& avatar_source = _getSourceAvatarOf(getAvartarWhenSourceIsModule());
		NENodeCodeSet& ns = connection.getSubParticles();

		//	post:
		NENode& avatar = ns[ns.push(avatar_source)];
		_onAvatarPushed(avatar, source, index_between_siblings);
		return avatar;
	}

	NENode& NodeVisualizer::_createAvartar(const NEKey& source, NENode& parent_of_avartar, type_int index_between_siblings)
	{
		typedef DX9Graphics::Model Model;
		Model& connection = _searchIn<DX9Graphics::Model>(parent_of_avartar);
		if( ! &connection) 
		{	
			ALERT_ERROR("parent_of_avartar에 DX9Graphics::Model 클래스가 없다.");
			__asm int 3;
		}
		NENode& avatar_source = _getSourceAvatarOf(getAvartarWhenSourceIsKey());
		NENodeCodeSet& ns = connection.getSubParticles();		

		//	post:
		NENode& avatar = ns[ns.push(avatar_source)];
		_onAvatarPushed(avatar, source, index_between_siblings);
		return avatar;
	}

	type_result NodeVisualizer::_searchInDepth(const NENode& target, type_int depth, type_int index_between_siblings, NENode& parent_of_avartar)
	{
		//	main:
		//		일단 나 자신을 만들고:
		NENode& my_avartar = _createAvartar(target, parent_of_avartar, index_between_siblings);
		//		하위 모듈을 탐색:
		const NEModuleCodeSet& modules = target.getModuleSet();
		for(int n=0; n < modules.getLength() ;n++)
			_searchInDepth(modules[n], depth+1, n, my_avartar);

		return RESULT_SUCCESS;
	}

	type_result NodeVisualizer::_searchInDepth(const NEModule& target, type_int depth, type_int index_between_siblings, NENode& parent_of_avartar)
	{
		//	main:
		//		내 아바타를 먼저 만들고:
		NENode& my_avartar = _createAvartar(target, parent_of_avartar, index_between_siblings);
		//		하위 키를 탐색:
		const NEKeyCodeSet& keys = target.getKeySet();
		for(int n=0; n < keys.getLength() ;n++)
			_searchInDepth(keys[n], depth+1, n, my_avartar);

		return RESULT_SUCCESS;
	}

	type_result NodeVisualizer::_searchInDepth(const NEKey& target, type_int depth, type_int index_between_siblings, NENode& parent_of_avartar)
	{
		//	main:
		//		내 아바타를 먼저 만들고:
		NENode& my_avartar = _createAvartar(target, parent_of_avartar, index_between_siblings);
		if(target.isSubClassOf(NEType::NENODE_CODESET_KEY))
		{
			const NENodeCodeSet& container = static_cast<const NENodeCodeSetKey&>(target).getValue();
			for(int n=0; n < container.getLength() ;n++)
				_searchInDepth(container[n], depth+1, n, my_avartar);
		}
		else if(target.isSubClassOf(NEType::NEMODULE_CODESET_KEY))
		{
			const NEModuleCodeSet& container = static_cast<const NEModuleCodeSetKey&>(target).getValue();
			for(int n=0; n < container.getLength() ;n++)
				_searchInDepth(container[n], depth+1, n, my_avartar);
		}	

		return RESULT_SUCCESS;
	}

	template<typename TYPE_TO_FIND>
	TYPE_TO_FIND& NodeVisualizer::_searchIn(NENode& target)
	{
		const NECodeSet& cs = TYPE_TO_FIND::getScriptCodeSet();
		NEModuleCodeSet& ms = target.getModuleSet();

		for(int n=0; n < ms.getLength() ;n++)
			if(cs.find(ms[n].getScriptCode()) != NE_INDEX_ERROR)
				return static_cast<TYPE_TO_FIND&>(ms[n]);

		TYPE_TO_FIND* nullptr = 0;
		return *nullptr;
	}

	NENode& NodeVisualizer::_getSourceAvatarOf(NENodeSelector& selector)
	{
		NENode& to_return = selector.getNode();
		selector.initializeReferingPoint();
		
		return to_return;
	}

	type_result NodeVisualizer::_onAvatarPushed(NENode& avatar, const NEModule& source, type_index index_between_siblings)
	{
		//	노드의 아바타가 생성될때:
		PanelBinder& binder = _searchIn<PanelBinder>(avatar);
		if( ! &binder)
		{
			ALERT_ERROR("생성하려는 모듈아바타에 PanelBinder가 없습니다.");
			return RESULT_TYPE_ERROR;
		}

		//	main:		
		//		원본에 딸린 모듈의 수만큼, 아바타의 모듈셋의 크기를 미리확장:
		DX9Graphics::Model& model = _searchIn<DX9Graphics::Model>(avatar);
		if( ! &model)
			ALERT_ERROR("아바타에 DX9Graphics::Model 이 없습니다. 계층구조 생성에 실패했습니다.")
		else
		{
			model.getSubParticles().create(source.getKeySet().getLength());
			_updateModelBy(model, index_between_siblings);
		}
		//		원본 노드와 바인딩:
		NEModuleSelector& to_be_binded = binder.getSourceSelector();
		to_be_binded.getBinder().bind(source, NEType::NESCRIPT_EDITOR);
		//		Text를 모듈의 이름으로 지정:
		using DX9Graphics::SpriteTexter;
		SpriteTexter& texter = _searchIn<SpriteTexter>(avatar);
		texter.getText() = source.getHeader().getName();

		return RESULT_SUCCESS;
	}

	type_result NodeVisualizer::_onAvatarPushed(NENode& avatar, const NENode& source, type_index index_between_siblings)
	{
		//	노드의 아바타가 생성될때:
		//		원본 노드와 바인딩:
		NodeBinder& binder = _searchIn<NodeBinder>(avatar);
		if( ! &binder)
		{
			ALERT_ERROR("생성하려는 노드아바타에 NodeBinder가 없습니다.");
			return RESULT_TYPE_ERROR;
		}

		//	main:
		//		원본에 딸린 모듈의 수만큼, 아바타의 모듈셋의 크기를 미리확장:
		DX9Graphics::Model& model = _searchIn<DX9Graphics::Model>(avatar);
		if( ! &model)
			ALERT_ERROR("아바타에 DX9Graphics::Model 이 없습니다. 계층구조 생성에 실패했습니다.")
		else
		{
			model.getSubParticles().create(source.getModuleSet().getLength());
			_updateModelBy(model, index_between_siblings);
		}
		NENodeSelector& to_be_binded = binder.getSourceSelector();
		to_be_binded.getBinder().bind(source, source.getManager().getType());
		//		Text를 "캐릭터"로 지정:
		using DX9Graphics::SpriteTexter;
		SpriteTexter& texter = _searchIn<SpriteTexter>(avatar);
		texter.getText() = "캐릭터";

		return RESULT_SUCCESS;
	}

	type_result NodeVisualizer::_onAvatarPushed(NENode& avatar, const NEKey& source, type_index index_between_siblings)
	{
		//	노드의 아바타가 생성될때:
		//		원본 노드와 바인딩:
		DX9Graphics::Model& model = _searchIn<DX9Graphics::Model>(avatar);
		KeyBinder& binder = _searchIn<KeyBinder>(avatar);
		if( ! &binder)
		{
			ALERT_ERROR("생성하려는 노드아바타에 KeyBinder가 없습니다.");
			return RESULT_TYPE_ERROR;
		}

		//	main:
		if(source.isSubClassOf(NEType::NENODE_CODESET_KEY))
		{
			//		원본에 딸린 모듈의 수만큼, 아바타의 모듈셋의 크기를 미리확장:
			if( ! &model)
				ALERT_ERROR("아바타에 DX9Graphics::Model 이 없습니다. 계층구조 생성에 실패했습니다.")
			else
			{
				NENodeCodeSetKey& casted = (NENodeCodeSetKey&) source;
				model.getSubParticles().create(casted.getValue().getLength());
			}
		}
		else if(source.isSubClassOf(NEType::NEMODULE_CODESET_KEY))
		{
			//		원본에 딸린 모듈의 수만큼, 아바타의 모듈셋의 크기를 미리확장:
			DX9Graphics::Model& model = _searchIn<DX9Graphics::Model>(avatar);
			if( ! &model)
				ALERT_ERROR("아바타에 DX9Graphics::Model 이 없습니다. 계층구조 생성에 실패했습니다.")
			else
			{
				NEModuleCodeSetKey& casted = (NEModuleCodeSetKey&) source;
				model.getSubParticles().create(casted.getValue().getLength());
			}
		}
		NEKeySelector& to_be_binded = binder.getSourceSelector();
		to_be_binded.getBinder().bind(source, NEType::NESCRIPT_EDITOR);
		//		Text를 "Key의 타입이름"로 지정:
		using DX9Graphics::SpriteTexter;
		SpriteTexter& texter = _searchIn<SpriteTexter>(avatar);
		texter.getText() = source.getTypeName();
		_updateModelBy(model, index_between_siblings);
		return RESULT_SUCCESS;
	}

	type_result NodeVisualizer::_onAvatarPushed(NENode& avatar, type_int length_to_create)
	{
		using namespace DX9Graphics;
		//	루트 노드의 아바타가 생성될때:
		//		스크립트의 수만큼 미리 Resize:
		Model& model = _searchIn<Model>(avatar);
		if( ! &model)
			ALERT_ERROR("아바타에 DX9Graphics::Model 이 없습니다.")
		else
			model.getSubParticles().create(length_to_create);
		//		Text를 "세계"로 지정:		
		SpriteTexter& texter = _searchIn<SpriteTexter>(avatar);
		texter.getText() = "세계";
		return RESULT_SUCCESS;
	}

}