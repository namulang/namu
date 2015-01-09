#include "Modifier.hpp"
#include "../Planetarium/Planetarium.hpp"

Modifier<NEBooleanKey>::Modifier(NEBooleanKey& key) 
	: Terminal("", NEType::NEBOOLEAN_KEY, 20, 7, 40, 7, WHITE, BLACK),
	sw(0, 38, 13, 4, LIGHTRED, WHITE), value(key.getValue()),
	name_lable(0, 0, 0, 8, 1, WHITE, LIGHTRED, "키 이름:"),
	value_lable(0, 0, 0, 8, 1, WHITE,LIGHTRED, "키 값:"), name_text(0, 0, 0, 22, 1, WHITE, BLACK),
	focused_text(1), real_key(&key)
{
	name_lable.y = y + 3;
	name_lable.x = x + 3;
	value_lable.y = name_lable.y + 2;
	value_lable.x = name_lable.x;
	name_text.x = sw.x = name_lable.x + name_lable.width;
	name_text.y = name_lable.y;
	sw.y = value_lable.y;
	sw.setValue(value);
	name_text.text = real_key ? real_key->getName() : "";

	regist(4, &sw, &name_lable, &value_lable, &name_text);
}

Modifier<NEBooleanKey>::Modifier(NEBooleanKey::Trait& new_value) 
	: Terminal("", NEType::NEBOOLEAN_KEY, 30, 10, 20, 5, WHITE, BLACK),
	sw(0, 38, 13, 4, LIGHTRED, WHITE), value(new_value), real_key(0)
{
	regist(1, &sw);
}


Modifier<NEBooleanKey>::Modifier(const Modifier& rhs) 
: Terminal(rhs), sw(rhs.sw), value(rhs.value), name_lable(rhs.name_lable),
value_lable(rhs.value_lable), name_text(rhs.name_text), focused_text(rhs.focused_text),
real_key(rhs.real_key)
{
	if(rhs.gliphs.getLength() > 2)
		regist(4, &sw, &name_lable, &value_lable, &name_text);
}


void Modifier<NEBooleanKey>::onUpdateData()
{
	Gliph&	focused = ! focused_text ? (Gliph&)name_text : sw,
	 	 &	else_one = &focused == &name_text ? (Gliph&) sw : name_text;

	focused.fore = WHITE;
	focused.back = LIGHTRED;
	else_one.fore = LIGHTGRAY;
	else_one.back = DARKGRAY;
	else_one.onUpdateData();
	focused.onUpdateData();
}

void Modifier<NEBooleanKey>::_setInputed(Gliph& target)
{
	target.fore = WHITE;
	target.back = LIGHTGREEN;
}

void Modifier<NEBooleanKey>::onKeyPressed(char inputed) 
{
	switch(inputed)
	{
	case UP:
		if(focused_text > 0)
		{
			focused_text--;
			onUpdateData();
		}
		break;

	case DOWN:
		if(focused_text < 1)
		{
			focused_text++;
			onUpdateData();
		}
		break;

	case CLOSE:			
		delete_me = true;
		break;

	case ENTER:
		if( ! focused_text && real_key)
		{
			real_key->getName() = name_text.text;
			_setInputed(name_text);
		}
		else
		{
			value = sw.getValue();

			_setInputed(sw);

			if( ! real_key)
				delete_me = true;
		}
		break;
	}

	if( ! focused_text)
		name_text.onKeyPressed(inputed);
	else
		sw.onKeyPressed(inputed);
}



Modifier<NENodeSelector>::Modifier()
: Window(14, 16, 42, 9, LIGHTGRAY, DARKGRAY),
header				(0, 15, 17, 10, 1, WHITE, LIGHTRED, "Manager"),
count_header		(0, 15, 18, 10, 1, WHITE, LIGHTRED, "Count"),
bind_header			(0, 15, 19, 10, 1, WHITE, LIGHTRED, "Bind?"),
code_type_header	(0, 15, 20, 10, 1, WHITE, LIGHTRED, "NodeType"),
use_and_header		(0,	15, 21, 10, 1, WHITE, LIGHTRED, "Use &&"),
peeking_lock_header	(0, 15, 22, 10, 1, WHITE, LIGHTRED, "PeekLock"),
codelist_header		(0, 15, 23, 10, 1, WHITE, LIGHTRED, "Codes")
{
	regist(8, &header, &count_header, &bind_header, &code_type_header, &use_and_header, &peeking_lock_header, &codelist_header, &menulist);
}


Modifier<NENodeSelector>::Modifier(const Modifier& rhs)
: Window(rhs), header(rhs.header), count_header(rhs.count_header), bind_header(rhs.bind_header), 
code_type_header(rhs.code_type_header), use_and_header(rhs.use_and_header), codelist_header(rhs.codelist_header), 
menulist(rhs.menulist), peeking_lock_header(rhs.peeking_lock_header)
{
	regist(8, &header, &count_header, &bind_header, &code_type_header, &use_and_header, &peeking_lock_header, &codelist_header, &menulist);
}


Modifier<NENodeSelector>::MenuList::MenuList() 
: ListGliph(0, 25, 17, 30, 7, BLACK, WHITE, WHITE, LIGHTRED), codelist_display_index(-1) {}

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
	case NECodeType::SCRIPT:	return banks.getBank(NECodeType::SCRIPT);
	case NECodeType::NAME:		return banks.getBank(NECodeType::NAME);
	case NECodeType::GROUP:		return banks.getBank(NECodeType::GROUP);
	case NECodeType::PRIORITY:	return banks.getBank(NECodeType::PRIORITY);
	default:		return *nullpointer;
	}
}

void Modifier<NENodeSelector>::MenuList::updateList()
{
	NENodeSelector& k = toOwner()->toCaller().toCaller().getNodeFilter();
	if( ! &k) return;

	NECodeType::CodeType type = k.getCodes().getCodeType().getCodeType();

	items.create(7);
	items.push(NEString("   ") + NEType::getTypeName(k.getManagerType()));
	items.push(NEString("   ") + k.getCountLimit());
	items.push(NEString("   ") + k.isUsingAutoBinding());
	items.push(NEString("   ") + createNodeTypeStringFrom(type));
	items.push(NEString("   ") + k.isUsingAndOperation());
	items.push(NEString("   ") + k.isPeekingLocked());

	const NETStringList& bank = getProperBankFrom(type);
	NEString codes_to_str;
	const NECodeSet& c = k.getCodes();
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
				codes_to_str += bank[c[n].getCode()] + "[" + c[n].getCode() + "] ";
		}
		else
			codes_to_str = "NOT NEEDED!";
		break;

	default:
		codes_to_str = NEString(codelist_display_index)+ "th: " + bank[c[codelist_display_index].getCode()] + "(" + c[codelist_display_index].getCode() + ")";
		break;
	}

	items.push("   " + codes_to_str);
}


void Modifier<NENodeSelector>::MenuList::onKeyPressed(char inputed)
{
	ListGliph::onKeyPressed(inputed);
	Planetarium& planetarium = toOwner()->toCaller().toCaller();
	NENodeSelector& key = planetarium.getNodeFilter();
	const NECodeType& type = key.getCodes().getCodeType();	

	switch(inputed)
	{
	case CONFIRM:
		if(choosed == 6)
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

					virtual void onFocused()
					{
						NENodeSelector& key = toCaller().toCaller().toCaller().getNodeFilter();
						NECodeType::CodeType type = key.getCodes().getCodeType().getCodeType();
						const NETStringList& bank = toCaller().menulist.getProperBankFrom(type);

						int n=0;
						for(const NETStringList::Iterator* itr=bank.getIterator(0); itr ;itr=itr->getNext())
							input.history.push(itr->getValue() + "(" + n++ + ")");

						input.history_idx = 0;
					}
					virtual void onUpdateData()
					{
						NEString& history = input.history[input.history_idx];
						if( &history)
							input.text = history;
					}
					virtual void onKeyPressed(char inputed)
					{
						switch(inputed)
						{
						case CLOSE:
						case ENTER:
						case LEFT:
						case RIGHT:
							InputWindow::onKeyPressed(inputed);
							break;
						}
					}

					virtual void onInputed()						
					{
						Planetarium& planetarium = toCaller().toCaller().toCaller();
						NENodeSelector& key = planetarium.getNodeFilter();
						NECodeSet copied = key.getCodes();
						if(copied.getLength() == copied.getSize())
							copied.resize(copied.getSize() + 1);
						copied.push(NECode(input.history_idx));
						key.setCodes(copied);
						planetarium.onUpdateData();
						toCaller().menulist.codelist_display_index = -1;
						toCaller().menulist.items.release();
						toCaller().menulist.onUpdateData();
						delete_me = true;
					}
				};

				NECodeType::CodeType type = key.getCodes().getCodeType().getCodeType();
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
				NECodeSet copied = key.getCodes();
				copied.remove(codelist_display_index);
				copied.resize(copied.getLength());
				key.setCodes(copied);
				if(codelist_display_index > copied.getLengthLastIndex())
					codelist_display_index = copied.getLengthLastIndex();

				planetarium.onUpdateData();

				items.release();
				onUpdateData();
			}
		}
		break;

	case UP:
	case DOWN:
		onUpdateData();
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
			switch(type.getCodeType())
			{
			case NECodeType::RECENT:	
				key.setCodesType(NECodeType::ME);
				break;
			case NECodeType::SCRIPT:
				key.setCodesType(NECodeType::RECENT);
				break;
			case NECodeType::NAME:
				key.setCodesType(NECodeType::SCRIPT);
				break;
			case NECodeType::GROUP:
				key.setCodesType(NECodeType::NAME);
				break;
			case NECodeType::PRIORITY:
				key.setCodesType(NECodeType::GROUP);
				break;					
			case NECodeType::ALL:
				key.setCodesType(NECodeType::PRIORITY);
				break;
			}
			break;

		case 4:	//	Use &&
			if(key.isUsingAndOperation())
				key.setUsingAndOperation(false);
			break;

		case 5:
			key.isPeekingLocked() = ! key.isPeekingLocked();
			break;

		case 6:
			if(codelist_display_index > -2)
				codelist_display_index--;
			break;
		}
		items.release();

		planetarium.onUpdateData();
		onUpdateData();
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
			switch(type.getCodeType())
			{
			case NECodeType::ME:
				key.setCodesType(NECodeType::RECENT);
				break;
			case NECodeType::RECENT:
				key.setCodesType(NECodeType::SCRIPT);
				break;
			case NECodeType::SCRIPT:
				key.setCodesType(NECodeType::NAME);
				break;
			case NECodeType::NAME:
				key.setCodesType(NECodeType::GROUP);
				break;
			case NECodeType::GROUP:
				key.setCodesType(NECodeType::PRIORITY);
				break;					
			case NECodeType::PRIORITY:
				key.setCodesType(NECodeType::ALL);
				break;
			}
			break;

		case 4:	//	Use &&
			if( ! key.isUsingAndOperation())
				key.setUsingAndOperation(true);
			break;

		case 5:
			key.isPeekingLocked() = ! key.isPeekingLocked();
			break;

		case 6:
			if(codelist_display_index < key.getCodes().getLengthLastIndex())
				codelist_display_index++;
		}
		items.release();
		planetarium.onUpdateData();
		onUpdateData();
		break;

	case CANCEL:
	case CLOSE:
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
			if(item.find(" ->") == NE_INDEX_ERROR)
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
	Planetarium& planetarium = toOwner()->toCaller().toCaller();
	NEModuleSelector& key = planetarium.getModuleFilter();
	NECodeType::CodeType module_type = key.getModuleCodes().getCodeType().getCodeType();

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

					virtual void onFocused()
					{
						lists.release();
						NEModuleSelector& key = toCaller().toCaller().toCaller().getModuleFilter();
						if(key.getModuleCodes().getCodeType().getCodeType() == NECodeType::MODULE_NAME) 
						{
							text = "새로 추가할 모듈 NameCode를 입력하세요.\n반드시 숫자로 입력하며, 자동 동기화가 안됩니다.";
							return;
						}

						const NEModuleSet& m = Kernal::getInstance().getModuleManager().getModuleSet();
						for(int n=0; n < m.getLength() ;n++)
						{
							input.history.push(m[n].getHeader().getName() + "(" + m[n].getScriptCode() + ")");
							lists.push(n);
						}

						input.history_idx = 0;
					}
					virtual void onUpdateData()
					{
						NEString& history = input.history[input.history_idx];
						if(&history)
							input.text = history;
					}

					virtual void onKeyPressed(char inputed)
					{
						switch(inputed)
						{
						case LEFT:
						case RIGHT:
						case CLOSE:
						case ENTER:
						case MAP:
							LG::InputWindow::onKeyPressed(inputed);
							break;

						default:
							if (toCaller().toCaller().toCaller().getModuleFilter().getModuleCodes().getCodeType().getCodeType() == NECodeType::MODULE_NAME)
								LG::InputWindow::onKeyPressed(inputed);
							break;
						}
					}

					virtual void onInputed()
					{
						Planetarium& planetarium = toCaller().toCaller().toCaller();
						NEModuleSelector& key = planetarium.getModuleFilter();

						NECodeSet copied = key.getModuleCodes();
						if(copied.getLength() == copied.getSize())
							copied.resize(copied.getSize() + 1);

						if(input.history_idx >= 0 && key.getModuleCodes().getCodeType().getCodeType() == NECodeType::SCRIPT)
							copied.push(NECode(lists[input.history_idx], NECodeType(NECodeType::SCRIPT, false)));
						else
							copied.push(NECode(input.text.toInt(), NECodeType(NECodeType::NAME, false)));

						key.setModuleCodes(copied);
						toCaller().menulist.codelist_display_index = -1;
						planetarium.onUpdateData();
						toCaller().menulist.items.release();
						toCaller().menulist.onUpdateData();
						delete_me = true;
					}

					NEListTemplate<type_index> lists;
				};

				switch(module_type)
				{
				case NECodeType::MODULE_SCRIPT:	case NECodeType::MODULE_NAME:
					toOwner()->call(CodeInputer());
					break;
				}

			}
			else if(codelist_display_index >= 0)
			{
				NECodeSet copied = key.getModuleCodes();
				copied.remove(codelist_display_index);
				copied.resize(copied.getLength());
				key.setModuleCodes(copied);
				if(codelist_display_index > copied.getLengthLastIndex())
					codelist_display_index = copied.getLengthLastIndex();

				planetarium.onUpdateData();

				items.release();
				onUpdateData();
			}
		}
		break;

	case UP:
	case DOWN:
		onUpdateData();
		break;

	case LEFT:
		switch(choosed)
		{
		case 0:	//	AutoBind
			if(key.isUsingAutoBinding())
				key.isUsingAutoBinding() = false;
			break;

		case 1:	//	CodeType
			switch(module_type)
			{
			case NECodeType::RECENT:
				key.setModuleCodesType(NECodeType::ME);
				break;
			case NECodeType::MODULE_SCRIPT:
				key.setModuleCodesType(NECodeType::RECENT);
				break;
			case NECodeType::MODULE_NAME:
				key.setModuleCodesType(NECodeType::MODULE_SCRIPT);
				break;				
			case NECodeType::ALL:
				key.setModuleCodesType(NECodeType::MODULE_NAME);
				break;
			}
			break;

		case 2:
			if(codelist_display_index > -2)
				codelist_display_index--;
			break;
		}
		items.release();
		onUpdateData();
		planetarium.onUpdateData();
		break;

	case RIGHT:
		switch(choosed)
		{
		case 0:	//	AutoBind
			if( ! key.isUsingAutoBinding())
				key.isUsingAutoBinding() = true;
			break;

		case 1:	//	CodeType
			switch(key.getModuleCodesType().getCodeType())
			{
			case NECodeType::ME:
				key.setModuleCodesType(NECodeType::RECENT);
				break;
			case NECodeType::RECENT:
				key.setModuleCodesType(NECodeType::MODULE_SCRIPT);
				break;
			case NECodeType::MODULE_SCRIPT:
				key.setModuleCodesType(NECodeType::MODULE_NAME);
				break;
			case NECodeType::MODULE_NAME:
				key.setModuleCodesType(NECodeType::ALL);
				break;
			}
			break;
		case 2:
			if(codelist_display_index < key.getModuleCodes().getLengthLastIndex())
				codelist_display_index++;
		}
		items.release();
		onUpdateData();
		planetarium.onUpdateData();
		break;

	case CANCEL:
	case CLOSE:
		toOwner()->delete_me = true;
	}			
}


void Modifier<NEKeySelector>::MenuList::onKeyPressed(char inputed)
{
	ListGliph::onKeyPressed(inputed);
	Planetarium& planetarium = toOwner()->toCaller().toCaller();
	NEKeySelector& key = planetarium.getKeyFilter();

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

				CodeInputer() : LG::InputWindow("새로 추가할 키의 이름을 좌우방향키로 선택하세요. \n물론 직접 이름을 입력 할 수도 있어요.", BLACK, WHITE) 
				{
				}

				virtual void onFocused()
				{
					NEKeySelector& filter = toCaller().toCaller().toCaller().getKeyFilter();

					//	ScriptEditor로 매니져 변경:
					//		현재는 아직 NodeManager, ScriptManager가 없기 때문에, 이쪽으로 셀렉터가
					//		찾도록 되어있는 경우는, 제대로 데이터를 가져올 수 없다.
					NEType::Type manager_backup = filter.getManagerType();
					filter.setManager(NEType::NESCRIPT_EDITOR);

					//	현재 Selector가 가져올 수 있는 노드들에 있는 모든 키 이름을 Preset으로 보내기:
					input.history.release();
					while(NENode* node = &filter.getNode())
					{
						const NEKeyCodeSet& ks = node->getKeySet();

						for(int n=0; n < ks.getLength() ;n++)
							if(input.history.find(ks[n].getName()) == NE_INDEX_ERROR)
								input.history.push(ks[n].getName());
					}
					filter.initializeReferingPoint();
					filter.setManager(manager_backup);

					input.history_idx = 0;
				}
				virtual void onUpdateData()
				{
					NEString& history = input.history[input.history_idx];
					if( &history)
						input.text = history;
				}

				virtual void onInputed()
				{
					Planetarium& planetarium = toCaller().toCaller().toCaller();
					NEKeySelector& key = planetarium.getKeyFilter();

					key.setKeyName(input.text);
					planetarium.onUpdateData();
					toCaller().menulist.items.release();
					toCaller().menulist.onUpdateData();
					delete_me = true;
				}
			};

			toOwner()->call(CodeInputer());					
		}
		break;

	case UP:
	case DOWN:
		onUpdateData();
		break;

	case LEFT:
		if(choosed == 0)
		{
			key.isUsingAutoBinding() = false;
			items.release();
			onUpdateData();	
		}				
		break;

	case RIGHT:
		if(choosed == 0)
		{
			key.isUsingAutoBinding() = true;
			items.release();
			onUpdateData();
		}
		break;

	case CANCEL:
	case CLOSE:
		toOwner()->delete_me = true;
	}			
}

void Modifier<NEModuleSelector>::MenuList::updateList()
{
	NEModuleSelector& k = toOwner()->toCaller().toCaller().getModuleFilter();
	if( ! &k) return;

	items.create(3);
	items.push(NEString("   ") + k.isUsingAutoBinding());
	items.push(NEString("   ") + createNodeTypeStringFrom(k.getModuleCodesType().getCodeType()));

	NEString codes_to_str;
	const NECodeSet& c = k.getModuleCodes();
	const NEModuleSet& ms = Kernal::getInstance().getModuleManager().getModuleSet();
	
	if(	k.getModuleCodesType() == NECodeType::ALL	||
		k.getModuleCodesType() == NECodeType::RECENT	||
		k.getModuleCodesType() == NECodeType::ME		)
	{
		codes_to_str = "NOT NEEDED!";				
		codelist_display_index = -1;
	}
	else
	{
		switch(codelist_display_index)
		{
		case -2:	codes_to_str = "NEW";	break;
		case -1:	
			codes_to_str = "CODES: ";
			{
				for(int n=0; n < c.getLength() ;n++)
				{
					const NEModule& f = ms[c[n].getCode()];
					if( ! &f) continue;

					codes_to_str += f.getHeader().getName() + "[" + c[n].getCode() + "] ";
				}
			}

			break;

		default:
			{
				const NEModule& f = ms[c[codelist_display_index].getCode()];
				if( ! &f)
					codes_to_str = "해당하는 모듈을 찾을 수 없습니다.";
				else
					codes_to_str = NEString(codelist_display_index) + 
						NEString("th: ") + f.getHeader().getName() + 
						NEString("[") + NEString(c[codelist_display_index].getCode()) + "]" ;
			}			
			break;
		}
	}

	items.push("   " + codes_to_str);
}

void Modifier<NEKeySelector>::MenuList::updateList()
{
	NEKeySelector& k = toOwner()->toCaller().toCaller().getKeyFilter();
	if( ! &k) return;

	items.create(2);
	items.push(NEString("   ") + k.isUsingAutoBinding());
	items.push(NEString("   ") + k.getKeyName());
}

const NETStringList& Modifier<NEModuleSelector>::MenuList::getProperBankFrom( NECodeType::CodeType type )
{
	const NEScriptEditor::Banks& banks = Editor::getInstance().getScriptEditor().getBanks();
	NETStringList* nullpointer = 0;
	switch(type)
	{
	case NECodeType::SCRIPT:	return banks.getBank(NECodeType::SCRIPT);
	case NECodeType::NAME:		return banks.getBank(NECodeType::NAME);
	case NECodeType::GROUP:		return banks.getBank(NECodeType::GROUP);
	case NECodeType::PRIORITY:	return banks.getBank(NECodeType::PRIORITY);
	default:		return *nullpointer;
	}
}