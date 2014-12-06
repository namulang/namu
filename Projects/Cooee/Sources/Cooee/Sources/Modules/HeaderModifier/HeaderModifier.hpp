#pragma once

#include "../../Includes/Includes.hpp"

/*
	ScriptHeader의 내용:
		Name,
		Developer,
		Revision,
		ReleaseDate,
		Version,
		Comment,
		Contact,
		MaxNameCodeIndex,		// AUTO
		MaxScriptCodeIndex,		// AUTO
		MaxGroupCodeIndex,		// AUTO
		MaxPriorityCodeIndex,	// AUTO
		ModuleLength,			// AUTO
		KeyLength,				// AUTO
		NodeLength,				// AUTO
*/

class HeaderModifier : public LG::ListWindow
{
public:
	HeaderModifier() 
		: LG::ListWindow("Header Modifier", 10, 4, 60, 13, BLACK, WHITE, WHITE, LIGHTGREEN)
	{
		codes_display_indexes.create(4);
		codes_display_indexes.push(-1);
		codes_display_indexes.push(-1);
		codes_display_indexes.push(-1);
		codes_display_indexes.push(-1);
	}
	HeaderModifier(const HeaderModifier& rhs)
		: LG::ListWindow(rhs), codes_display_indexes(rhs.codes_display_indexes) {}
	FUNC_CLONE(HeaderModifier)
	virtual void onUpdateData()
	{
		ListWindow::onUpdateData();

		NEScriptManager::ScriptHeader& h = Editor::getInstance().getScriptEditor().getScriptHeader();

		list.items.create(6+codes_display_indexes.getLength());
		list.items.push("이  름 : " + h.getName());
		list.items.push("개발자 : " + h.getDeveloper());
		list.items.push("개  정 : " + NEString(h.getRevision()));
		list.items.push("출시일 : " + h.getReleaseDate());
		list.items.push("설  명 : " + h.getComment());
		list.items.push("연락처 : " + h.getContact());

		_pushCodeLists();
	}

	void _pushCodeLists();
	NEString _generateCodeListNames(int index);

	class StringInputWindow : public LG::InputWindow
	{
	public:
		StringInputWindow(NETString& data)
			: LG::InputWindow("새로운 값을 입력하세요", BLACK, YELLOW, data),
			string_to_be_changed(data) {}
		StringInputWindow(const StringInputWindow& rhs)
			: LG::InputWindow(rhs), string_to_be_changed(rhs.string_to_be_changed) {}
		FUNC_CLONE(StringInputWindow)
		virtual void onInputed()
		{
			string_to_be_changed = input.text;
			delete_me = true;
		}

		NETString& string_to_be_changed;
	};

	//	선택한 코드에 대하여 어떠한 작업을 수행할 것인지를 선택하는 메뉴
	class CodePopUpMenu : public LG::ListWindow
	{
	public:
		CodePopUpMenu(NECodeType::CodeType codetype, type_index code)
			: LG::ListWindow("Code PopUp Menu", 20, 9, 25, 6, BLACK, WHITE, WHITE, LIGHTBLUE), _codetype(codetype), _code(code)
		{
			if(_code < 0)
			{
				type_index to_return = _getMaxCodeIndex(_codetype) + 1;
				if(to_return == -2)
				{
					EDITOR_WARNING(" : 잘못된 ScriptHeader의 코드를 조작하려 했습니다.");

					delete_me = true;
				}
				
				_code = to_return;
			}
		}

		type_index _getMaxCodeIndex(NECodeType::CodeType from)
		{
			const NEScriptManager::ScriptHeader& h = Editor::getInstance().getScriptEditor().getScriptHeader();
			switch(from)
			{
			case NECodeType::NAME:
				return h.getMaxNameCodeIndex();
			case NECodeType::GROUP:
				return h.getMaxGroupCodeIndex();
			case NECodeType::PRIORITY:
				return h.getMaxPriorityCodeIndex();
			default:
				return -2;
			}
		}

		CodePopUpMenu(const CodePopUpMenu& rhs)
			: LG::ListWindow(rhs), _codetype(rhs._codetype), _code(rhs._code) {}
		FUNC_CLONE(CodePopUpMenu)
		FUNC_TO_CALLER(HeaderModifier)
		
		virtual void onUpdateData()
		{
			LG::ListWindow::onUpdateData();

			if(_codetype == NECodeType::SCRIPT)
			{
				list.items.create(1);
				list.items.push("이름 수정하기");
			}
			else
			{
				list.items.create(3);
				list.items.push("[" + NEString(_code) + "]에 새로운 코드 삽입");
				list.items.push("이름 수정하기");
				list.items.push("삭제하기");
			}
			
		}

		virtual void onItemChoosed(type_index index, const NEString& chosen_content);
		void _onModifyCodeName();
		void _onAddNewCode();
		void _onRemoveCode();

		NECodeType::CodeType _codetype;
		type_index _code;
	};
	
	virtual void onItemChoosed(type_index index, const NEString& chosen_content);
	virtual void onKeyPressed(char inputed);

	NEIntSet codes_display_indexes;
};