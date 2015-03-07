#include "HeaderModifier.hpp"
#include "../Core/Core.hpp"

namespace 
{
	NETStringList& _getProperBankBy(NECodeType::CodeType codetype)
	{
		NEScriptEditor::Banks& banks = Editor::getInstance().getScriptEditor().getBanks();

		switch(codetype)
		{
		case NECodeType::NAME:		return banks.getBank(NECodeType::NAME);
		case NECodeType::SCRIPT:	return banks.getBank(NECodeType::SCRIPT);
		case NECodeType::GROUP:		return banks.getBank(NECodeType::GROUP);
		case NECodeType::PRIORITY:	return banks.getBank(NECodeType::PRIORITY);
		}

		NETStringList* nullpointer = 0x00;
		return *nullpointer;
	}

	const NETStringList& _getProperBankBy(int index)
	{
		const NEScriptEditor::Banks& banks = Editor::getInstance().getScriptEditor().getBanks();

		switch(index)
		{
		case 0:	return banks.getBank(NECodeType::NAME);
		case 1: return banks.getBank(NECodeType::SCRIPT);
		case 2: return banks.getBank(NECodeType::GROUP);
		case 3: return banks.getBank(NECodeType::PRIORITY);
		}

		NETStringList* nullpointer = 0x00;
		return *nullpointer;
	}
}

void HeaderModifier::CodePopUpMenu::onItemChoosed(type_index index, const NEString& chosen_content)
{
	NEScriptEditor& ed = Editor::getInstance().getScriptEditor();
	if(_codetype == NECodeType::SCRIPT)
	{
		if(index == 0)
			_onModifyCodeName();

		return;
	}

	switch(index)
	{
	case 0:    
		//    새로운 코드 삽입:
		_onAddNewCode();
		break;

	case 1:    //    이름 수정하기
		_onModifyCodeName();
		break;

	case 2:	//	코드 삭제하기
		_onRemoveCode();
		break;

	default:
		::Core::pushMessage("ERROR: 그러한 명령은 없습니다.");
		return;
	}
}

void HeaderModifier::CodePopUpMenu::_onModifyCodeName()
{
	NETStringList& bank = _getProperBankBy(_codetype);
	if( ! &bank[_code])
	{
		::Core::pushMessage("ERROR: 주어진 이름이 존재하지 않습니다.");
		return;
	}
	call(StringInputWindow(bank[_code]));
	delete_me = true;
}

void HeaderModifier::CodePopUpMenu::_onAddNewCode()
{
	if( ! _code)
	{
		::Core::pushMessage("ERROR: 0번 코드는 기본 코드입니다. 추가 / 삭제가 불가능합니다.");
		return;
	}
	if(Editor::getInstance().getEventHandler().isTestRunning())
	{
		::Core::pushMessage("ERROR: 이 작업을 수행하려면, 디버깅을 먼저 종료해야 합니다.");
		return;
	}

	NEScriptEditor& ed = Editor::getInstance().getScriptEditor();

	if( ! NEResult::hasError(ed.insertCode(NECode(_code, _codetype))))
		_onModifyCodeName();
}


void HeaderModifier::CodePopUpMenu::_onRemoveCode()
{
	if( ! _code)
	{
		::Core::pushMessage("ERROR: 0번 코드는 기본 코드입니다. 추가 / 삭제가 불가능합니다.");
		return;
	}
	if(Editor::getInstance().getEventHandler().isTestRunning())
	{
		::Core::pushMessage("ERROR: 이 작업을 수행하려면, 디버깅을 먼저 종료해야 합니다.");
		return;
	}
	NEScriptEditor& ed = Editor::getInstance().getScriptEditor();

	ed.removeCode(NECode(_code, _codetype));

	//	UI의 탐색커서를 하나 감소시키기:
	type_index cursor = NE_INDEX_ERROR;
	switch (_codetype)
	{
	case NECodeType::NAME:		cursor = 0;	break;
	case NECodeType::SCRIPT:	cursor = 1; break;
	case NECodeType::GROUP:		cursor = 2; break;
	case NECodeType::PRIORITY:	cursor = 3; break;
	}
	if(cursor >= 0)
	{
		type_code& code = toCaller().codes_display_indexes[cursor];
		if(	&code		&&
			code > 0	)
			code--;
	}


	delete_me = true;
}

void HeaderModifier::onItemChoosed(type_index index, const NEString& chosen_content)
{
	NEScriptHeader& h = Editor::getInstance().getScriptEditor().getScriptHeader();
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

		{
			type_code code = codes_display_indexes[index-6];
			if(code != -1)
				call(CodePopUpMenu(ct, code));
		}		
		break;
	}
}

void HeaderModifier::_pushCodeLists()
{
	const NEScriptEditor::Banks& banks = Editor::getInstance().getScriptEditor().getBanks();

	for(int code_type_n=0; code_type_n < codes_display_indexes.getLength(); code_type_n++)
	{
		NEString to_show = (list.choosed == code_type_n + 6) ? "<-" : "  ";

		switch(code_type_n)
		{
		case 0:	to_show += "[NAME] "; break;
		case 1: to_show += "[SCRI] "; break;
		case 2: to_show += "[GROU] "; break;
		case 3: to_show += "[PRIO] "; break;
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
				if (index >= 0)
				{
					const NETStringList& bank = _getProperBankBy(code_type_n);
					if(index > bank.getLengthLastIndex())
						index = bank.getLengthLastIndex();

					to_show += bank[index];
				}

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

		if(to_show.getLength() > 40)
		{
			to_show += "...";
			break;
		}
	}

	return to_show;
}

void HeaderModifier::onKeyPressed(char inputed)
{
	int codetype = list.choosed - 6;
	if(codetype >= 0 && codetype <= 3)
	{
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

	ListWindow::onKeyPressed(inputed);

	onUpdateData();
}