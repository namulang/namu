#include "Modifier.hpp"
#include "../Planetarium/Planetarium.hpp"

Modifier<NEBooleanKey>::Modifier(NEBooleanKey& key) 
	: Terminal("", NEType::NEBOOLEAN_KEY, 30, 10, 20, 5, WHITE, BLACK),
	sw(0, 38, 13, 4, LIGHTRED, WHITE), value(key.getValue())
{
	regist(1, &sw);
}

Modifier<NEBooleanKey>::Modifier(NEBooleanKey::Trait& new_value) 
	: Terminal("", NEType::NEBOOLEAN_KEY, 30, 10, 20, 5, WHITE, BLACK),
	sw(0, 38, 13, 4, LIGHTRED, WHITE), value(new_value)
{
	regist(1, &sw);
}


Modifier<NEBooleanKey>::Modifier(const Modifier& rhs) 
	: Terminal(rhs), sw(rhs.sw), value(rhs.value)
{
	regist(1, &sw);
}


void Modifier<NEBooleanKey>::onUpdateData()
{
	sw.setValue(value);
}


void Modifier<NEBooleanKey>::onKeyPressed(char inputed) 
{
	Terminal::onKeyPressed(inputed);

	switch(inputed) 
	{
	case CONFIRM:
		value = sw.getValue();

	case CANCEL:
		delete_me = true;
		break;
	}
}



Modifier<NENodeSelector>::Modifier(NENodeSelector& new_key)
	: FilterModifier(4, 17, 52, 8, LIGHTGRAY, DARKGRAY), key(new_key),
	header			(0, 15, 18, 10, 1, WHITE, LIGHTRED, "Manager"),
	count_header	(0, 15, 19, 10, 1, WHITE, LIGHTRED, "Count"),
	bind_header		(0, 15, 20, 10, 1, WHITE, LIGHTRED, "Bind?"),
	code_type_header(0, 15, 21, 10, 1, WHITE, LIGHTRED, "NodeType"),
	use_and_header	(0,	15, 22, 10, 1, WHITE, LIGHTRED, "Use &&"),
	codelist_header	(0, 15, 23, 10, 1, WHITE, LIGHTRED, "Codes")
{
	regist(7, &header, &count_header, &bind_header, &code_type_header, &use_and_header, &codelist_header, &menulist);
}


Modifier<NENodeSelector>::Modifier(const Modifier& rhs)
	: FilterModifier(rhs), key(rhs.key), header(rhs.header), count_header(rhs.count_header), bind_header(rhs.bind_header), 
	code_type_header(rhs.code_type_header), use_and_header(rhs.use_and_header), codelist_header(rhs.codelist_header), 
	menulist(rhs.menulist)
{
	regist(7, &header, &count_header, &bind_header, &code_type_header, &use_and_header, &codelist_header, &menulist);
}


Modifier<NENodeSelector>::MenuList::MenuList() 
	: ListGliph(0, 25, 18, 30, 6, BLACK, WHITE, WHITE, LIGHTRED), codelist_display_index(-1) {}

NEString Modifier<NENodeSelector>::MenuList::createNodeTypeStringFrom(NECodeType::CodeType type)
{
	switch(type)
	{
	case NECodeType::ME:		return "ME";
	case NECodeType::GROUP:		return "GROUP";
	case NECodeType::SCRIPT:	return "SCRIPT";
	case NECodeType::NAME:		return "NAME";
	case NECodeType::PRIORITY:	return "PRIORITY";
	case NECodeType::RECENT:	return "RECENT";
	case NECodeType::ALL:		return "ALL";
	default:					return "ERROR! UNKNOWN!";
	}
}

const NETStringList& Modifier<NENodeSelector>::MenuList::getProperBankFrom(NECodeType::CodeType type)
{
	const NEScriptEditor::Banks& banks = Editor::getInstance().getScriptEditor().getBanks();
	NETStringList* nullpointer = 0;
	switch(type)
	{
	case NECodeType::SCRIPT:	return banks.getScriptBank();
	case NECodeType::NAME:		return banks.getNameBank();
	case NECodeType::GROUP:		return banks.getGroupBank();
	case NECodeType::PRIORITY:	return banks.getPriorityBank();
	default:		return *nullpointer;
	}
}

void Modifier<NENodeSelector>::MenuList::updateList()
{
	NENodeSelector& k = toOwner()->key;
	if( ! &k) return;

	items.create(6);
	items.push(NEString("   ") + NEType::getTypeName(k.getManagerType()));
	items.push(NEString("   ") + k.getCountLimit());
	items.push(NEString("   ") + k.isUsingAutoBinding());
	items.push(NEString("   ") + createNodeTypeStringFrom(k.getNodeType()));
	items.push(NEString("   ") + k.isUsingAndOperation());

	const NETStringList& bank = getProperBankFrom(k.getNodeType());
	NEString codes_to_str;
	const NEIntSet& c = k.getCodeSet();
	if( ! &bank)
		codelist_display_index = -1;
	switch(codelist_display_index)
	{
	case -2:	codes_to_str = "NEW";	break;
	case -1:	
		if( &bank)
		{				
			codes_to_str = "CODES: ";
			for(int n=0; n < c.getLength() ;n++)
				codes_to_str += bank[c[n]] + " ";
		}
		else
			codes_to_str = "NOT NEEDED!";
		break;

	default:
		codes_to_str = NEString("[") + codelist_display_index + "]" + bank[c[codelist_display_index]] + "(" + c[codelist_display_index] + ")";
		break;
	}

	items.push("   " + codes_to_str);
}


void Modifier<NENodeSelector>::MenuList::onKeyPressed(char inputed)
{
	ListGliph::onKeyPressed(inputed);
	NENodeSelector& key = toOwner()->key;

	switch(inputed)
	{
	case CONFIRM:
		if(choosed == 5)
		{
			if(codelist_display_index == -2)
			{
				class CodeInputer : public LG::InputWindow
				{
				public:
					FUNC_TO_CALLER(Modifier<NENodeSelector>)
					virtual NEObject& clone() const { return *(new CodeInputer(*this)); }
					CodeInputer() : LG::InputWindow("새로 추가할 CODE를 좌우 방향키로 선택하세요", BLACK, WHITE) 
					{

					}

					virtual void onUpdateData()
					{
						const NETStringList& bank = toCaller().menulist.getProperBankFrom(toCaller().key.getNodeType());								

						int n=0;
						for(const NETStringList::Iterator* itr=bank.getIterator(0); itr ;itr=itr->getNext())
							input.history.push(itr->getValue() + "(" + n++ + ")");

						input.history_idx = 0;
						input.text = input.history[input.history_idx];
					}
					virtual void onKeyPressed(char inputed)
					{
						switch(inputed)
						{
						case CANCEL:
						case CONFIRM:
						case LEFT:
						case RIGHT:
							InputWindow::onKeyPressed(inputed);
							break;
						}
					}

					virtual void onInputed()						
					{
						NEIntSet copied = toCaller().key.getCodeSet();
						if(copied.getLength() == copied.getSize())
							copied.resize(copied.getSize() + 1);
						copied.push(input.history_idx);
						toCaller().key.setCodeSet(copied);
						toCaller().getPlanetarium().onUpdateData();
						toCaller().getPlanetarium().onDraw();
						toCaller().menulist.items.release();
						toCaller().menulist.onUpdateData();
						toCaller().menulist.onDraw();
						delete_me = true;
					}
				};

				NECodeType::CodeType type = toOwner()->key.getNodeType();
				switch(type)
				{
				case NECodeType::SCRIPT:	case NECodeType::GROUP: 
				case NECodeType::PRIORITY:	case NECodeType::NAME:
					toOwner()->call(CodeInputer());
					break;
				}

			}
			else if(codelist_display_index >= 0)
			{
				NEIntSet copied = toOwner()->key.getCodeSet();
				copied.remove(codelist_display_index);
				copied.resize(copied.getLength());
				toOwner()->key.setCodeSet(copied);
				if(codelist_display_index > copied.getLengthLastIndex())
					codelist_display_index = copied.getLengthLastIndex();

				toOwner()->getPlanetarium().onUpdateData();
				toOwner()->getPlanetarium().onDraw();

				items.release();
				onUpdateData();
				onDraw();
			}
		}
		break;

	case UP:
	case DOWN:
		onUpdateData();
		onDraw();
		break;

	case LEFT:
		switch(choosed)
		{
		case 0:	//	ManageType
			switch(key.getManagerType())
			{
			case NEType::NENODE_MANAGER:	
				key.setManager(NEType::NESCRIPT_MANAGER);						
				break;
			case NEType::NESCRIPT_EDITOR:
				key.setManager(NEType::NENODE_MANAGER);
				break;
			}					
			break;

		case 1:	//	Count
			if(key.getCountLimit() > 0)
				key.setCountLimit(key.getCountLimit()-1);
			break;

		case 2:	//	AutoBind
			if(key.isUsingAutoBinding())
				key.isUsingAutoBinding() = false;
			break;

		case 3:	//	CodeType
			switch(key.getNodeType())
			{
			case NECodeType::RECENT:
				key.setNodeType(NECodeType::ME);
				break;
			case NECodeType::SCRIPT:
				key.setNodeType(NECodeType::RECENT);
				break;
			case NECodeType::NAME:
				key.setNodeType(NECodeType::SCRIPT);
				break;
			case NECodeType::GROUP:
				key.setNodeType(NECodeType::NAME);
				break;
			case NECodeType::PRIORITY:
				key.setNodeType(NECodeType::GROUP);
				break;					
			case NECodeType::ALL:
				key.setNodeType(NECodeType::PRIORITY);
				break;
			}
			break;
		case 4:	//	Use &&
			if(key.isUsingAndOperation())
				key.setUsingAndOperation(false);
			break;

		case 5:
			if(codelist_display_index > -2)
				codelist_display_index--;
			break;
		}
		items.release();

		toOwner()->getPlanetarium().onUpdateData();
		toOwner()->getPlanetarium().onDraw();
		onUpdateData();
		onDraw();
		break;

	case RIGHT:
		switch(choosed)
		{
		case 0:	//	ManageType
			switch(key.getManagerType())
			{
			case NEType::NESCRIPT_MANAGER:	
				key.setManager(NEType::NENODE_MANAGER);
				break;
			case NEType::NENODE_MANAGER:
				key.setManager(NEType::NESCRIPT_EDITOR);
				break;
			}					
			break;

		case 1:	//	Count
			key.setCountLimit(key.getCountLimit()+1);
			break;

		case 2:	//	AutoBind
			if( ! key.isUsingAutoBinding())
				key.isUsingAutoBinding() = true;
			break;

		case 3:	//	CodeType
			switch(key.getNodeType())
			{
			case NECodeType::ME:
				key.setNodeType(NECodeType::RECENT);
				break;
			case NECodeType::RECENT:
				key.setNodeType(NECodeType::SCRIPT);
				break;
			case NECodeType::SCRIPT:
				key.setNodeType(NECodeType::NAME);
				break;
			case NECodeType::NAME:
				key.setNodeType(NECodeType::GROUP);
				break;
			case NECodeType::GROUP:
				key.setNodeType(NECodeType::PRIORITY);
				break;					
			case NECodeType::PRIORITY:
				key.setNodeType(NECodeType::ALL);
				break;
			}
			break;

		case 4:	//	Use &&
			if( ! key.isUsingAndOperation())
				key.setUsingAndOperation(true);
			break;

		case 5:
			if(codelist_display_index < key.getCodeSet().getLengthLastIndex())
				codelist_display_index++;
		}
		items.release();
		toOwner()->getPlanetarium().onUpdateData();
		toOwner()->getPlanetarium().onDraw();
		onUpdateData();
		onDraw();
		break;

	case CANCEL:
		toOwner()->delete_me = true;
	}
}

void Modifier<NENodeSelector>::MenuList::onUpdateData()
{
	if(items.getLength() < 6)
		updateList();

	for(int n=0; n < 6 ;n++)
	{
		NEString& item = items[n];
		if(n == choosed)
		{
			item[0] = '<';
			item[1] = '-';
			item[2] = ' ';
			item += " ->";
		}
		else if(item.getLength() > 0 && item[0] == '<')
		{
			item[0] = ' ';
			item[1] = ' ';
			item[2] = ' ';
			item.pop();
			item.pop();
			item.pop();
			item[item.getLengthLastIndex()] = '\0';
		}
	}

}

void Modifier<NEModuleSelector>::MenuList::onKeyPressed(char inputed)
{
	ListGliph::onKeyPressed(inputed);
	NEModuleSelector& key = toOwner()->key;

	switch(inputed)
	{
	case CONFIRM:
		if(choosed == 2)
		{
			if(codelist_display_index == -2)
			{
				class CodeInputer : public LG::InputWindow
				{
				public:
					FUNC_TO_CALLER(Modifier<NEModuleSelector>)
					virtual NEObject& clone() const { return *(new CodeInputer(*this)); }
					CodeInputer() : LG::InputWindow("새로 추가할 CODE를 입력하세요.", BLACK, WHITE) 
					{

					}

					virtual void onInputed()
					{
						NECodeSet copied = toCaller().key.getModuleCodeSet();
						if(copied.getLength() == copied.getSize())
							copied.resize(copied.getSize() + 1);
						copied.push(input.text.toInt());
						toCaller().key.setModuleCodeSet(copied);
						toCaller().getPlanetarium().onUpdateData();
						toCaller().getPlanetarium().onDraw();
						toCaller().menulist.items.release();
						toCaller().menulist.onUpdateData();
						toCaller().menulist.onDraw();
						delete_me = true;
					}
				};

				NECodeType::CodeType type = toOwner()->key.getModuleType();
				switch(type)
				{
				case NECodeType::SCRIPT:	case NECodeType::NAME:
					toOwner()->call(CodeInputer());
					break;
				}

			}
			else if(codelist_display_index >= 0)
			{
				NECodeSet copied = toOwner()->key.getModuleCodeSet();
				copied.remove(codelist_display_index);
				copied.resize(copied.getLength());
				toOwner()->key.setModuleCodeSet(copied);
				if(codelist_display_index > copied.getLengthLastIndex())
					codelist_display_index = copied.getLengthLastIndex();

				toOwner()->getPlanetarium().onUpdateData();
				toOwner()->getPlanetarium().onDraw();

				items.release();
				onUpdateData();
				onDraw();
			}
		}
		break;

	case UP:
	case DOWN:
		onUpdateData();
		onDraw();
		break;

	case LEFT:
		switch(choosed)
		{
		case 0:	//	AutoBind
			if(key.isUsingAutoBinding())
				key.isUsingAutoBinding() = false;
			break;

		case 1:	//	CodeType
			switch(key.getModuleType())
			{
			case NECodeType::RECENT:
				key.setModuleType(NECodeType::ME);
				break;
			case NECodeType::SCRIPT:
				key.setModuleType(NECodeType::RECENT);
				break;
			case NECodeType::NAME:
				key.setModuleType(NECodeType::SCRIPT);
				break;				
			case NECodeType::ALL:
				key.setModuleType(NECodeType::NAME);
				break;
			}
			break;

		case 2:
			if(codelist_display_index > -2)
				codelist_display_index--;
			break;
		}
		items.release();
		toOwner()->onUpdateData();
		toOwner()->onDraw();
		break;

	case RIGHT:
		switch(choosed)
		{
		case 0:	//	AutoBind
			if( ! key.isUsingAutoBinding())
				key.isUsingAutoBinding() = true;
			break;

		case 1:	//	CodeType
			switch(key.getModuleType())
			{
			case NECodeType::ME:
				key.setModuleType(NECodeType::RECENT);
				break;
			case NECodeType::RECENT:
				key.setModuleType(NECodeType::SCRIPT);
				break;
			case NECodeType::SCRIPT:
				key.setModuleType(NECodeType::NAME);
				break;
			case NECodeType::NAME:
				key.setModuleType(NECodeType::ALL);
				break;
			}
			break;
		case 2:
			if(codelist_display_index < key.getModuleCodeSet().getLengthLastIndex())
				codelist_display_index++;
		}
		items.release();
		toOwner()->onUpdateData();
		toOwner()->onDraw();
		break;

	case CANCEL:
		toOwner()->delete_me = true;
	}			
}


void Modifier<NEKeySelector>::MenuList::onKeyPressed(char inputed)
{
	ListGliph::onKeyPressed(inputed);
	NEKeySelector& key = toOwner()->key;

	switch(inputed)
	{
	case CONFIRM:
		if(choosed == 1)
		{			
			class CodeInputer : public LG::InputWindow
			{
			public:
				FUNC_TO_CALLER(Modifier<NEKeySelector>)
				virtual NEObject& clone() const { return *(new CodeInputer(*this)); }

				CodeInputer(const NEStringList& names) : LG::InputWindow("새로 추가할 키의 이름을 좌우방향키로 선택하세요. \n물론 직접 이름을 입력 할 수도 있어요.", BLACK, WHITE) 
				{
					input.history = names;
					input.history_idx = 0;
					input.text = input.history[input.history_idx];
				}

				virtual void onInputed()
				{
					toCaller().key.setKeyName(input.text);
					toCaller().getPlanetarium().onUpdateData();
					toCaller().getPlanetarium().onDraw();
					toCaller().menulist.items.release();
					toCaller().menulist.onUpdateData();
					toCaller().menulist.onDraw();
					delete_me = true;
				}
			};

			//	ScriptEditor로 매니져 변경:
			//		현재는 아직 NodeManager, ScriptManager가 없기 때문에, 이쪽으로 셀렉터가
			//		찾도록 되어있는 경우는, 제대로 데이터를 가져올 수 없다.
			NEType::Type manager_backup = key.getManagerType();
			key.setManager(NEType::NESCRIPT_EDITOR);

			//	현재 Selector가 가져올 수 있는 노드들에 있는 모든 키 이름을 Preset으로 보내기:
			NEStringList bucket;
			NENode* itr=0;
			while(itr = &key.getNode())
			{
				NEKeyCodeSet& ks = itr->getKeySet();

				for(int n=0; n < ks.getLength() ;n++)
					if(bucket.find(ks[n].getName()) == NE_INDEX_ERROR)
						bucket.push(ks[n].getName());
			}

			key.initializeReferingPoint();
			key.setManager(manager_backup);
			toOwner()->call(CodeInputer(bucket));					
		}
		break;

	case UP:
	case DOWN:
		onUpdateData();
		onDraw();
		break;

	case LEFT:
		if(choosed == 0)
		{
			key.isUsingAutoBinding() = false;
			items.release();
			onUpdateData();
			onDraw();		
		}				
		break;

	case RIGHT:
		if(choosed == 0)
		{
			key.isUsingAutoBinding() = true;
			items.release();
			onUpdateData();
			onDraw();
		}
		break;

	case CANCEL:
		toOwner()->delete_me = true;
	}			
}