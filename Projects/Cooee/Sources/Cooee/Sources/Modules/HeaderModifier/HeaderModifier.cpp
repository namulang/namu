#include "HeaderModifier.hpp"
#include "../Core/Core.hpp"

namespace 
{
	class StringInputWindow : public LG::InputWindow
	{
	public:
		StringInputWindow(NETString& data)
			: LG::InputWindow("새로운 값을 입력하세요", BLACK, YELLOW, data),
			string_to_be_changed(data) {}
		StringInputWindow(const StringInputWindow& rhs)
			: InputWindow(rhs), string_to_be_changed(rhs.string_to_be_changed) {}

		virtual void onInputed()
		{
			string_to_be_changed = input.text;
		}

		NETString& string_to_be_changed;
	};

	NETStringList& _getProperBankBy(NECodeType::CodeType codetype)
	{
		NEScriptEditor::Banks& banks = Editor::getInstance().getScriptEditor().getBanks();

		switch(codetype)
		{
		case NECodeType::NAME:		return banks.getNameBank();
		case NECodeType::SCRIPT:	return banks.getScriptBank();
		case NECodeType::GROUP:		return banks.getGroupBank();
		case NECodeType::PRIORITY:	return banks.getPriorityBank();
		}

		NETStringList* nullpointer = 0x00;
		return *nullpointer;
	}

	const NETStringList& _getProperBankBy(int index)
	{
		const NEScriptEditor::Banks& banks = Editor::getInstance().getScriptEditor().getBanks();

		switch(index)
		{
		case 0:	return banks.getNameBank();
		case 1: return banks.getScriptBank();
		case 2: return banks.getGroupBank();
		case 3: return banks.getPriorityBank();
		}

		NETStringList* nullpointer = 0x00;
		return *nullpointer;
	}
}

void HeaderModifier::CodePopUpMenu::onItemChoosed(type_index index, const NEString& chosen_content)
{
	if(	_codetype < NECodeType::NAME	||
		_codetype > NECodeType::PRIORITY)
	{
		::Core::pushMessage("ERROR: 잘못된 CodeType입니다.");
		delete_me = true;
		return;
	}
	NEScriptEditor& ed = Editor::getInstance().getScriptEditor();

	switch(index)
	{
	case 0:	
		//	새로운 코드 삽입:
		if(_codetype == NECodeType::SCRIPT)
			_onModifyCodeName();
		else
			_onAddNewCode();

		break;
	case 1:	//	이름 수정하기
		_onModifyCodeName();
		break;

	case 2:	//	코드 삭제하기
		_onRemoveCode();

	default:
		::Core::pushMessage("ERROR: 그러한 명령은 없습니다.");
		return;
	}
}

void HeaderModifier::CodePopUpMenu::_onModifyCodeName()
{
	NETStringList& bank = _getProperBankBy(_codetype);
	call(StringInputWindow(bank[_code]));
	delete_me = true;
}

void HeaderModifier::CodePopUpMenu::_onAddNewCode()
{
	NEScriptEditor& ed = Editor::getInstance().getScriptEditor();

	switch(_codetype)
	{
	case NECodeType::NAME:		ed.insertNameCode(_code);		break;
	case NECodeType::GROUP:		ed.insertGroupCode(_code);		break;
	case NECodeType::PRIORITY:	ed.insertPriorityCode(_code);	break;				
	}

	_onModifyCodeName();
}


void HeaderModifier::CodePopUpMenu::_onRemoveCode()
{
	NEScriptEditor& ed = Editor::getInstance().getScriptEditor();

	switch(_codetype)
	{
	case NECodeType::NAME:		ed.removeNameCode(_code);		break;
	case NECodeType::GROUP:		ed.removeGroupCode(_code);		break;
	case NECodeType::PRIORITY:	ed.removePriorityCode(_code);	break;
	}

	delete_me = true;
}

void HeaderModifier::onItemChoosed(type_index index, const NEString& chosen_content)
{
	NEScriptManager::ScriptHeader& h = Editor::getInstance().getScriptEditor().getScriptHeader();
	NECodeType::CodeType ct = NECodeType::UNDEFINED;
	switch(index)
	{
	case 0:	//	이름 변경하기
		call( StringInputWindow(h.getName()));
		break;

	case 1:
		call( StringInputWindow(h.getDeveloper()));
		break;

	case 2:
		::Core::pushMessage("Revision은 자동으로 증가됩니다.");
		break;

	case 3:
		call( StringInputWindow(h.getReleaseDate()));
		break;

	case 4:
		call( StringInputWindow(h.getComment()));
		break;

	case 5:
		call( StringInputWindow(h.getContact()));
		break;

	case 6:	//	Bank 선택시
		ct = NECodeType::NAME;
	case 7:
		if(ct == NECodeType::UNDEFINED)
			ct = NECodeType::SCRIPT;
	case 8:
		if(ct == NECodeType::UNDEFINED)
			ct = NECodeType::GROUP;
	case 9:	
		if(ct == NECodeType::UNDEFINED)
			ct = NECodeType::PRIORITY;

		call(CodePopUpMenu(ct, codes_display_indexes[index-6]));
		break;
	}
}

void HeaderModifier::_pushCodeLists()
{
	const NEScriptEditor::Banks& banks = Editor::getInstance().getScriptEditor().getBanks();

	for(int code_type_n=0; code_type_n < codes_display_indexes.getLength(); code_type_n++)
	{
		NEString to_show;
		if(list.choosed == code_type_n + 6)
			to_show = "<-";
		switch(code_type_n)
		{
		case 0:	to_show = "[NAME] "; break;
		case 1: to_show = "[SCRI] "; break;
		case 2: to_show = "[GROU] "; break;
		case 3: to_show = "[PRIO] "; break;
		}

		int index = codes_display_indexes[code_type_n];
		switch(index)
		{
		case -2:
			to_show += "NEW";
			break;

		case -1:	
			to_show += _generateCodeListNames(code_type_n);
			break;

		default:
			{
				to_show += NEString(index) + "th: ";
				if(index >= 0)
					to_show += _getProperBankBy(code_type_n)[index];
			}
		}

		if(list.choosed == code_type_n + 6)
		to_show += "->";
		list.items.push(to_show);
	}
}

NE::NEString HeaderModifier::_generateCodeListNames(int index)
{
	NEString to_show = "CODES: ";
	const NETStringList& bank = _getProperBankBy(index);

	int n=0;
	for(const NETStringList::Iterator* i = bank.getIterator(0); i ;i = i->getNext())
	{
		to_show += i->getValue().extract(0, 4) + "[" + n++ + "] ";	//	5글자씩만

		if(to_show.getLength() > 23)								//	최대 20글자까지만 출력
			break;
	}

	return to_show;
}

void HeaderModifier::onKeyPressed(char inputed)
{
	ListWindow::onUpdateData();

	int codetype = list.choosed - 6;
	if(codetype < 6	||	codetype > 9)	return;
	const NETStringList& bank = _getProperBankBy(codetype);

	switch(inputed)
	{
	case LEFT:
		if(codes_display_indexes[codetype] > -2)
			codes_display_indexes[codetype]--;
		break;

	case RIGHT:
		if(codes_display_indexes[codetype] < bank.getLengthLastIndex())
			codes_display_indexes[codetype]++;
		break;
	}
}