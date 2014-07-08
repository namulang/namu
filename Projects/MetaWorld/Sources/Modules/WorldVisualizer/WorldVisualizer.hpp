#pragma once

#include "../../Includes/Includes.hpp"

namespace MetaWorld
{
	class NE_DLL WorldVisualizer : public NEModule
	{
	public:
		typedef WorldVisualizer ThisClass;
		typedef NEModule SuperClass;

	public:
		NENodeSelector& getVisualNodeSelector()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NENodeSelector&>(casted->getVisualNodeSelector());
		}
		const NENodeSelector& getVisualNodeSelector() const
		{
			const NEKey& key = getKeySet()[0];
			if( ! &key || ! key.isSubClassOf(NEType::NENODE_SELECTOR))
			{
				ALERT_ERROR("0번키는 NENODE_SELECTOR여야 합니다.");
				const NENodeSelector* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NENodeSelector&>(key);
		}
		NEKeySelector& getScriptCodeSelector()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NEKeySelector&>(casted->getScriptCodeSelector());
		}
		const NEKeySelector& getScriptCodeSelector() const
		{
			const NEKey& key = getKeySet()[1];
			if( ! &key || ! key.isSubClassOf(NEType::NEKEY_SELECTOR))
			{
				ALERT_ERROR("1번키는 NEKEY_SELECTOR여야 합니다.");
				const NEKeySelector* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEKeySelector&>(key);
		}

	public:
		virtual type_result initialize()
		{
			NEKeyCodeSet& cont = getKeySet();
			cont.create(2);
			cont.push(NENodeSelector());	//	0:	노드를 찾으면 이 셀렉터를 찾은 노드를 재귀적으로 생성한다. 단, 이안에는 1개 이상의 Model 혹은 AnimatedModel이 있어야 한다.
			cont.push(NEKeySelector());		//	1:	0번 노드를 추가하기전에, ScriptEditor의 무슨 Script를 가리키는지 이 키에 적어놓는다.
			return RESULT_SUCCESS;
		}
		virtual type_result execute();
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if(_instance.getName().getSize() <= 0)
			{
				_instance.getName() = "WorldVisualizer";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2013-10-21";
				_instance.getVersion() = "0.0.1a";
				_instance.getComment() = "ScriptEditor에 노드가 나올때마다 0번에 있는 노드를 생성해줍니다.\n생성시에는 계층구조를 고려하는데, 예를들어 ScriptEditor에 Node1안에 Node2가 속해있는 형태라면, \n 이것을 본딴 형태로 NodeManager에 만들어 줍니다. 0번키로부터 나온 노드는 최소 1개 이상의 \nModel/AnimatedModel과 1번키가 저장할 IntKey를 가지고 있어야 합니다.\n0: 생성하게될 Node(처음 1개 외에는 무시)\n1: 0번 노드가 가지고 있는, ScriptEditor의 ScriptCode를 가리키는 값을 저장할 키";
			}

			return _instance;
		}
		virtual NEObject& clone() const { return *(new ThisClass(*this)); }

	private:		
		DX9Graphics::Model& _castFrom(NEModule& module);
		type_result _searchModuleSet(NEModuleCodeSet& sources_in_editor, NENodeCodeSet& targets_in_noder);
		type_result _searchKeySet(NEKeyCodeSet& sources_in_editor, NENodeCodeSet& targets_in_noder);
		type_result _searchNodeSet(NENodeCodeSet& sources_in_editor, NENodeCodeSet& targets_in_noder);
		type_result _updateKeyToGivenScriptCode(NENode& to_be_push, type_code scriptcode);
		NENodeCodeSet& _getInnerContainer(NENode& target);		
	};
}