#include "WorldVisualizer.hpp"

namespace MetaWorld
{
	type_result WorldVisualizer::execute()
	{
		NENodeCodeSet	&se = Editor::getInstance().getScriptEditor().getScriptNodes(),
						&nm = Kernal::getInstance().getNodeManager().getRootNodes();
		

		return _searchNodeSet(se, nm);
	}

	DX9Graphics::Model& WorldVisualizer::_castFrom(NEModule& module)
	{
		using namespace DX9Graphics;
	
		if(DX9Graphics::Model::getScriptCodeSet().find(module.getScriptCode()) != NE_INDEX_ERROR)
			return static_cast<Model&>(module);

		Model* nullpoint = 0;
		return *nullpoint;
	}

	type_result WorldVisualizer::_searchModuleSet(NEModuleCodeSet& sources_in_editor, NENodeCodeSet& targets_in_noder)
	{
		return 0;
	}

	type_result WorldVisualizer::_searchKeySet(NEKeyCodeSet& sources_in_editor, NENodeCodeSet& targets_in_noder)
	{
		return 0;
	}

	type_result WorldVisualizer::_searchNodeSet(NENodeCodeSet& sources_in_editor, NENodeCodeSet& targets_in_noder)
	{
		//	알고리즘:
		//		목적:
		//			ScriptEditor의 노드간의 계층구조를 그대로 본따서 NodeManager
		//			에 추가한다.
		//			이때, 
		//				1 - NodeManager에는 0번키에서 추출한 노드A 1개를 대신 push하며, 
		//				2 - 노드A는 AnimatedModel, Model을 1개 이상 가지고 있어야 하며,
		//				3 - 1번키에 노드A가 몇번 스크립트코드임을 붙여넣기 한다.
		//			이 스크립트코드는 일반적으로 노드A안에 있는 걸 사용한다.
		//			그래서 NodeManager에 추가된 노드들이 ScriptEditor의 무슨 
		//			스크립트에서 "본따왔는가"를 알 수 있도록 "추적성"을 제공한다.
		//
		//		절차:
		//			1	- 대신 push할 노드A를 찾는다.
		//			2	- sources를 탐색하는데, 각각의 노드를 source라 하자.
		//				sources에 있는 모든 노드를 찾는데,
		//			3	- source의 ScriptCode를 구한다. 1번키에 주입하기 위해서다.
		//			4	- 1번키에서 찾은 모든 키에 그 값을 대입한다. 
		//				(= _updateKeyToGivenScriptCode)
		//			5	- 노드A를 targets에 push 한다.
		//			6	- source안에 또 노드가 있는지 NodeCodeSetKey를 탐색한다.
		//				(= _getInnerContainer)
		//			7	- 있다면,
		//			7-1	- 새로운 sources로 다시 시작.
		//			7-2	- 없다면, 2번으로 돌아간다.
		//
		//		핵심 식별자 설명:
		//			sources_in_editor	- 탐색할 Source. ScriptEditor에 위치하고 있으며, 이
		//								노드들을 본따게 된다. (const)
		//			source				- Editor 안에 있는 노드 1개.
		//			targets_in_noder	- 탐색한 Source가 추가될 장소.
		//			recruit				- 대신 push될 노드. 0번키에서 1개만 가져온다.		


		//	pre:		
		NENodeSelector& sel = getVisualNodeSelector();
		NENode& recruit = sel.getNode();
		if( ! &recruit)
		{
			ALERT_ERROR("0번키에 노드가 없습니다.");
			return RESULT_TYPE_ERROR;
		}
		sel.initializeReferingPoint();	//	0번키에서 노드 1개만 targets_in_noder에 push 한다.
		

		//	main:
		for(int n=0; n < sources_in_editor.getSize() ;n++)
		{
			NENode& source = sources_in_editor[n];
			//	ScriptCode 할당:
			//_updateKeyToGivenScriptCode(source.getScriptCode());
			//	삽입:
			//		resize:
			if(targets_in_noder.getSize() == targets_in_noder.getLength())
				targets_in_noder.resize(targets_in_noder.getSize() + 1);
			//		insertion:
			//targets_in_noder.
			//	재귀 탐색:
			//type_index where_new_one_was_pushed = targets_in_noder.push();
			//if(NENodeCodeSet& is_this_new_push_to = _getInnerContainer(nodeset[where_new_one_was_pushed]))
		}
		return 0;
	}

	NENodeCodeSet& WorldVisualizer::_getInnerContainer(NENode& target)
	{
		NENodeCodeSet* nullptr = 0;
		return *nullptr;
	}

	type_result WorldVisualizer::_updateKeyToGivenScriptCode(NENode& to_be_push, type_code scriptcode)
	{
		return 0;
	}
}