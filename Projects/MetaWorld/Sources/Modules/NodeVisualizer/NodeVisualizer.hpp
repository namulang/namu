#pragma once

#include "../../Includes/Includes.hpp"

namespace MetaWorld
{
	class NE_DLL NodeVisualizer : public NEModule
	{
	public:
		typedef NodeVisualizer ThisClass;
		typedef NEModule SuperClass;

	public:
		const NENodeSelector& getSources() const
		{
			const NEKey& key = getKeySet()[0];
			if( ! &key || ! key.isSubClassOf(NEType::NENODE_SELECTOR))
			{
				ALERT_ERROR("0번키는 NODE_SELECTOR여야 합니다.");
				NENodeSelector* nullptr = 0;
				return *nullptr;
			}

			return static_cast<const NENodeSelector&>(key);
		}
		NENodeSelector& getSources()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NENodeSelector&>(casted->getSources());
		}
		const NENodeSelector& getAvartarWhenSourceIsMostAncestor() const
		{
			const NEKey& key = getKeySet()[1];
			if( ! &key || ! key.isSubClassOf(NEType::NENODE_SELECTOR))
			{
				ALERT_ERROR("1번키는 NODE_SELECTOR여야 합니다.");
				NENodeSelector* nullptr = 0;
				return *nullptr;
			}

			return static_cast<const NENodeSelector&>(key);
		}
		NENodeSelector& getAvartarWhenSourceIsMostAncestor()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NENodeSelector&>(casted->getAvartarWhenSourceIsMostAncestor());
		}
		const NENodeSelector& getAvartarWhenSourceIsNode() const
		{
			const NEKey& key = getKeySet()[2];
			if( ! &key || ! key.isSubClassOf(NEType::NENODE_SELECTOR))
			{
				ALERT_ERROR("2번키는 NODE_SELECTOR여야 합니다.");
				NENodeSelector* nullptr = 0;
				return *nullptr;
			}

			return static_cast<const NENodeSelector&>(key);
		}
		NENodeSelector& getAvartarWhenSourceIsNode()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NENodeSelector&>(casted->getAvartarWhenSourceIsNode());
		}
		const NENodeSelector& getAvartarWhenSourceIsModule() const
		{
			const NEKey& key = getKeySet()[3];
			if( ! &key || ! key.isSubClassOf(NEType::NENODE_SELECTOR))
			{
				ALERT_ERROR("3번키는 NODE_SELECTOR여야 합니다.");
				NENodeSelector* nullptr = 0;
				return *nullptr;
			}

			return static_cast<const NENodeSelector&>(key);
		}
		NENodeSelector& getAvartarWhenSourceIsModule()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NENodeSelector&>(casted->getAvartarWhenSourceIsModule());
		}
		const NENodeSelector& getAvartarWhenSourceIsKey() const
		{
			const NEKey& key = getKeySet()[4];
			if( ! &key || ! key.isSubClassOf(NEType::NENODE_SELECTOR))
			{
				ALERT_ERROR("4번키는 NODE_SELECTOR여야 합니다.");
				NENodeSelector* nullptr = 0;
				return *nullptr;
			}

			return static_cast<const NENodeSelector&>(key);
		}
		NENodeSelector& getAvartarWhenSourceIsKey()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NENodeSelector&>(casted->getAvartarWhenSourceIsKey());
		}
		const type_float& getDeltaXPerDepth() const
		{
			const NEKey& key = getKeySet()[5];
			if( ! &key || ! key.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("5번키는 NEFLOAT_KEY여야 합니다.");
				type_float* nullptr = 0;
				return *nullptr;
			}

			return static_cast<const NEFloatKey&>(key).getValue();
		}
		type_float& getDeltaXPerDepth()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_float&>(casted->getDeltaXPerDepth());
		}
		const type_float& getDeltaYPerDepth() const
		{
			const NEKey& key = getKeySet()[6];
			if( ! &key || ! key.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("6번키는 NEFLOAT_KEY여야 합니다.");
				type_float* nullptr = 0;
				return *nullptr;
			}

			return static_cast<const NEFloatKey&>(key).getValue();
		}
		type_float& getDeltaYPerDepth()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_float&>(casted->getDeltaYPerDepth());
		}
		const type_float& getDeltaZPerDepth() const
		{
			const NEKey& key = getKeySet()[7];
			if( ! &key || ! key.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("7번키는 NEFLOAT_KEY여야 합니다.");
				type_float* nullptr = 0;
				return *nullptr;
			}

			return static_cast<const NEFloatKey&>(key).getValue();
		}
		type_float& getDeltaZPerDepth()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_float&>(casted->getDeltaZPerDepth());
		}
		const type_float& getDeltaXPerIndex() const
		{
			const NEKey& key = getKeySet()[8];
			if( ! &key || ! key.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("8번키는 NEFLOAT_KEY여야 합니다.");
				type_float* nullptr = 0;
				return *nullptr;
			}

			return static_cast<const NEFloatKey&>(key).getValue();
		}
		type_float& getDeltaXPerIndex()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_float&>(casted->getDeltaXPerIndex());
		}
		const type_float& getDeltaYPerIndex() const
		{
			const NEKey& key = getKeySet()[9];
			if( ! &key || ! key.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("9번키는 NEFLOAT_KEY여야 합니다.");
				type_float* nullptr = 0;
				return *nullptr;
			}

			return static_cast<const NEFloatKey&>(key).getValue();
		}
		type_float& getDeltaYPerIndex()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_float&>(casted->getDeltaYPerIndex());
		}
		const type_float& getDeltaZPerIndex() const
		{
			const NEKey& key = getKeySet()[10];
			if( ! &key || ! key.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("10번키는 NEFLOAT_KEY여야 합니다.");
				type_float* nullptr = 0;
				return *nullptr;
			}

			return static_cast<const NEFloatKey&>(key).getValue();
		}
		type_float& getDeltaZPerIndex()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_float&>(casted->getDeltaZPerIndex());
		}

	public:
		virtual type_result initialize()
		{
			NEKeyCodeSet& ks = getKeySet();
			ks.create(11);
			NENodeSelector s;
			s.setManager(NEType::NESCRIPT_EDITOR);
			ks.push(s);					//	0:	시각화 데이터를 만들 최상위 개념원본들.
			s.setManager(NEType::NESCRIPT_MANAGER);
			ks.push(s);	//	1:	최상위 노드를 데이터로 만들때 사용할 복사 원본
			ks.push(s);	//	2:	노드를 데이터로 생성할때 사용할 복사원본
			ks.push(s);	//	3:	모듈를 데이터로 생성할때 사용할 복사원본
			ks.push(s);	//	4:	키를 데이터로 생성할때 사용할 복사원본
			ks.push(NEFloatKey(0));		//	5:	하나의 깊이당 X변화
			ks.push(NEFloatKey(0));		//	6:	하나의 깊이당 Y변화
			ks.push(NEFloatKey(10));	//	7:	하나의 깊이당 Z변화
			ks.push(NEFloatKey(0));		//	8:	하나의 인덱스당 X변화
			ks.push(NEFloatKey(10));	//	9:	하나의 인덱스당 Y변화
			ks.push(NEFloatKey(0));		//	10:	하나의 인덱스당 Z변화
			return RESULT_SUCCESS;
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if(_instance.getName().getSize() <= 0)
			{
				_instance.getName() = "NodeVisualizer";
				_instance.setRevision(1);
				_instance.getDeveloper() = "kniz";
				_instance.getComment() = "0: 시각화데이터를 만들 대상(하위노드도 탐색한다)\n1: 최상위 노드의 아바타\n2:노드의 아바타\n3:모듈의 아바타\n4:키의 아바타\n5:깊이당 X변화\n6:깊이당 Y변화\n7:깊이당 Z변화\n8:인덱스당 X변화:\n9:인덱스당 Y변화\n10:인덱스당 Z변화";
			}

			return _instance;
		}

	public:
		virtual type_result execute()
		{
			using namespace NE;
			//	pre:
			//		최상위 노드의 아바타를 생성하기:
			NENodeSelector& srcs_sel = getSources();

			//	main:
			//		만약 특정 노드가 지정되었다면:
			//			그 노드 안에만 실시:
			if(srcs_sel.getNodeType() != NECodeType::ALL)
			{	//			루트 노드 길이 측정:
				int length = 0;
				while(&srcs_sel.getNode())
					length++;
				
				NENode& avartar_of_soma/*StubOfMostAncestor*/ = _createAvartar(length);

				type_int index = 0;
				while(NENode* src = &srcs_sel.getNode())
					_searchInDepth(*src, 0, index++, avartar_of_soma);
			}
			else	//		루트 노드 길이 측정:
			{	
				const NENodeCodeSet& scripts = Editor::getInstance().getScriptEditor().getScriptNodes();
				
				NENode& avartar_of_soma = _createAvartar(scripts.getLength());

				for(int n=0; n < scripts.getLength() ;n++)
					_searchInDepth(scripts[n], 0, n, avartar_of_soma);
			}
			
			return RESULT_SUCCESS;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	private:
		NENode& _createAvartar(type_int length);
		NENode& _createAvartar(const NENode& source, NENode& parent_of_avartar, type_int index_between_siblings);
		NENode& _createAvartar(const NEModule& source, NENode& parent_of_avartar, type_int index_between_siblings);
		NENode& _createAvartar(const NEKey& source, NENode& parent_of_avartar, type_int index_between_siblings);
		type_result _searchInDepth(const NENode& target, type_int depth, type_int index_between_siblings, NENode& parent_of_avartar);
		type_result _searchInDepth(const NEModule& target, type_int depth, type_int index_between_siblings, NENode& parent_of_avartar);
		type_result _searchInDepth(const NEKey& target, type_int depth, type_int index_between_siblings, NENode& parent_of_avartar);
		template <typename TYPE_TO_FIND>
		TYPE_TO_FIND& _searchIn(NENode& target);
		NENode& _getSourceAvatarOf(NENodeSelector& selector);
		type_result _onAvatarPushed(NENode& avatar, type_int length_to_create);
		type_result _onAvatarPushed(NENode& avatar, const NENode& source, type_index index_between_siblings);
		type_result _onAvatarPushed(NENode& avatar, const NEModule& source, type_index index_between_siblings);
		type_result _onAvatarPushed(NENode& avatar, const NEKey& source, type_index index_between_siblings);
		type_result _updateModelBy(DX9Graphics::Model& model, type_index index_between_siblings)
		{
			model.getTranslationX() = getDeltaXPerDepth() + getDeltaXPerIndex() * index_between_siblings;
			model.getTranslationY() = getDeltaYPerDepth() + getDeltaYPerIndex() * index_between_siblings;
			model.getTranslationZ() = getDeltaZPerDepth() + getDeltaZPerIndex() * index_between_siblings;

			return RESULT_SUCCESS;
		}
	};
}