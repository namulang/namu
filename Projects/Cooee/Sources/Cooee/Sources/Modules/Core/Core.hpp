#pragma once

#include "../Commander/Commander.hpp"
#include "../ModuleSetTerminal/ModuleSetTerminal.hpp"

class Core
{
public:	
	static NEObject& getCurrentObjectFromPath()
	{
		return getObjectBy(path);
	}
	static void pushMessage(const NEString& msg)
	{
		::LG::Core::windows.pushFront(LG::MessageWindow(msg, WHITE, LIGHTRED));
	}
	static void openModifierFrom(const NEString& path);
	static void openModifierFrom(NEKey& key);
	static type_index _getPositionTypeAndIndex(const NEString& position, int& type)
	{
		int index_to_be_returned = position.getLength() > 1 ? position.extract(0, position.getLengthLastIndex()).toInt() : NE_INDEX_ERROR;
		
		switch(position[0])
		{
		case 'n':	type = 1;	break;	// node
		case 'm':	type = 2;	break;	// module
		case 'k':	type = 3;	break;	// key
		default:	type = 0;			// auto
		}

		return index_to_be_returned;
	}

	static NEObject& _searchModuleSet(NEModuleCodeSet& moduleset, NEStringSet& work_position)
	{
		//	pre:
		NEObject* null_pointer = NE_NULL;	
		if( ! &work_position)
		{
			pushMessage("작업위치 문자열이 없습니다.");
			return *null_pointer;
		}
		if(work_position.getLength() <= 0)
			return moduleset;
		NEString& position = work_position[0];
		int type = 0; // 0은 unknown을 의미한다.
		int index = _getPositionTypeAndIndex(position, type);
		if(type != 0 && type != 2)
		{
			pushMessage(NEString("잘못된 위치 문자열입니다 : " + position + "타입이 모듈이 아닙니다."));
			return *null_pointer;
		}
		if(index < 0 || index > moduleset.getLengthLastIndex())
		{
			pushMessage("잘못된 인덱스. 0보다 작거나, 모듈셋의 크기를 넘습니다.");
			return *null_pointer;
		}



		//	main:
		NEModule& module = moduleset[index];
		work_position.popFront();			
		if(work_position.getLength() > 0)
			pushMessage("어라? 모듈은 경로가 마지막에 해당하는데, 뒤에 또 뭐가 있네요? 경로가 꼬인듯?\n일단, 모듈만 반환합니다.");

		return module;
	}

	static NEObject& _searchKeySet(NEKeyCodeSet& keyset, NEStringSet& work_position)
	{
		//	pre:
		NEObject* null_pointer = NE_NULL;	
		if( ! &work_position)
		{
			pushMessage("작업위치 문자열이 없습니다.\n");
			return keyset;
		}
		if(work_position.getLength() <= 0)
			return keyset;
		NEString& position = work_position[0];
		int type = 0; // 0은 unknown을 의미한다.
		int index = position.toInt();


		//	main:
		NEKey& key = keyset[index];

		work_position.popFront();
		if(key.isSubClassOf(NEType::NEMODULE_CODESET_KEY))
		{
			NEModuleCodeSetKey& modulesetkey = static_cast<NEModuleCodeSetKey&>(key);
			NEModuleCodeSet& moduleset = modulesetkey.getValue();

			return _searchModuleSet(moduleset, work_position);			
		} 
		else if(key.isSubClassOf(NEType::NENODE_CODESET_KEY))
		{
			NENodeCodeSetKey& managed_nodesetkey = static_cast<NENodeCodeSetKey&>(key);
			NENodeCodeSet& nodeset = managed_nodesetkey.getValue();

			return _searchNodeSet(nodeset, work_position);
		}
		
		return key;
	}

	static NEObject& _searchNodeSet(NENodeCodeSet& nodeset, NEStringSet& work_position)
	{
		//	pre:
		NEObject* null_pointer = NE_NULL;	
		if( ! &work_position)
		{
			pushMessage("작업위치 문자열이 없습니다.");
			return *null_pointer;
		}
		if(work_position.getLength() <= 0)
		{
			pushMessage("문자열이 잘못되었습니다. 제대로 /를 사용해서 위치를 구분했나요?");
			return *null_pointer;
		}
		NEString& position = work_position[0];
		int type = 0; // 0은 unknown을 의미한다.
		int index = _getPositionTypeAndIndex(position, type);
		if(type != 0 && type != 1)
		{
			pushMessage(NEString("잘못된 위치 문자열입니다 : " + position + "타입이 노드가 아닙니다."));
			return *null_pointer;
		}
		if(index < 0 || index > nodeset.getLengthLastIndex())
		{
			pushMessage("잘못된 인덱스. 0보다 작거나, 노드셋의 크기를 넘습니다.");
			return *null_pointer;
		}



		//	main:
		NENode& node = nodeset[index];

		work_position.popFront();
		if(work_position.getLength() > 0)
		{
			NEModuleCodeSet& moduleset = node.getModuleSet();

			return _searchModuleSet(moduleset, work_position);
		}
		else
			return node;
	}
	static NEObject& getObjectBy(const NEString& path);
	static NEString createPathBy(const NEObject& target);

	static Commander commander;
	static NEString path;
};