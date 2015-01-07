#pragma once

#include "../InputTerminal/InputTerminal.hpp"
#include "../NameInputWindow/NameInputWindow.hpp"

template <typename KEY>
class Modifier : public InputTerminal
{
public:
	Modifier(KEY& key)
		: InputTerminal("", "주어진 키의 새로운 값을 입력하세요", KEY().getType()),
		value(key.getValue()), name_lable(0, 0, 0, 8, 1, WHITE, LIGHTRED, "키 이름:"),
		value_lable(0, 0, 0, 8, 1, WHITE, LIGHTRED, "키 값:"), name_text(0, 0, 0, 22, 1, WHITE, BLACK),
		focused_text(0), real_key(&key)
	{
		y -= 3;
		height += 6;
		name_lable.y = y + 3;
		name_lable.x = x + 3;
		value_lable.y = y + 5;
		value_lable.x = x + 3;
		name_text.x = textbox.x = name_lable.x + name_lable.width;
		name_text.y = name_lable.y;
		textbox.y = value_lable.y;
		textbox.width = name_text.width;
		textbox.text = value;
		name_text.text = real_key ? real_key->getName() : "";

		regist(3, &name_lable, &value_lable, &name_text);
	}
	Modifier(typename KEY::Trait& new_value)
		: InputTerminal("", "주어진 키의 새로운 값을 입력하세요", NEType::NEKEY), 
		value_lable(0, 0, 0, 8, 1, WHITE, LIGHTRED, "키 값:"), focused_text(1), value(new_value), real_key(0)
	{
		textbox.text = value;
		regist(1, &value_lable);
	}
	Modifier(const Modifier& rhs) : InputTerminal(rhs), value(rhs.value), focused_text(rhs.focused_text),
		value_lable(rhs.value_lable), name_text(rhs.name_text), name_lable(rhs.name_lable), 
		real_key(rhs.real_key)
	{
		if(rhs.gliphs.getLength() > 2)
			regist(3, &name_lable, &value_lable, &name_text);
	}

	virtual void onUpdateData()
	{
		TextGliph&	focused = ! focused_text ? name_text : textbox,
			&	else_one = &focused == &name_text ? textbox : name_text;

		focused.fore = WHITE;
		focused.back = LIGHTRED;
		else_one.fore = LIGHTGRAY;
		else_one.back = DARKGRAY;
	}

	virtual void onKeyPressed(char inputed)
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
				KEY temp(value);
				temp = NEStringKey(textbox.text);
				value = temp.getValue();

				_setInputed(textbox);

				if( ! real_key)
					delete_me = true;
			}
			break;
		}

		if( ! focused_text)
			name_text.onKeyPressed(inputed);
		else
			textbox.onKeyPressed(inputed);			
	}

	void _setInputed(Gliph& target)
	{
		target.fore = WHITE;
		target.back = LIGHTGREEN;
	}

	virtual void onTextInputed()
	{		
	}

	typename KEY::Trait& value;
	KEY* real_key;
	FUNC_CLONE(Modifier<KEY>)

		Gliph name_lable, value_lable;
	TextGliph name_text;
	int focused_text;
};



template <>
class Modifier<NEBooleanKey> : public Terminal
{
public:
	Modifier(NEBooleanKey& key);
	Modifier(NEBooleanKey::Trait& new_value);
	Modifier(const Modifier& rhs);

	virtual void onUpdateData();
	virtual void onKeyPressed(char inputed);
	void _setInputed(Gliph& target);
	FUNC_CLONE(Modifier<NEBooleanKey>)

		LG::SwitchGliph sw;
	NEBooleanKey::Trait& value;
	NEBooleanKey* real_key;
	Gliph name_lable, value_lable;
	TextGliph name_text;
	int focused_text;
};

template <>
class Modifier<NECodeKey> : public Terminal
{
public:
	Modifier(NECodeKey& key)
		: Terminal("", NEType::NECODE_KEY, 20, 8, 40, 5, BLACK, WHITE),
		name_lable(0, 22, 9, 8, 1, WHITE, LIGHTRED, "키 이름:"),		
		type_lable(0, 22, 10, 8, 1, WHITE, LIGHTRED, "Code Type:"),
		value_lable(0, 22, 11, 8, 1, WHITE, LIGHTRED, "Code:"),
		name_text(0, 30, 9, 28, 1, WHITE, BLACK),
		type_text(0, 30, 10, 28, 1, WHITE, BLACK),
		value_text(0, 30, 11, 28, 1, WHITE, BLACK),
		focused(0), real_key(&key), value(key.getValue())
	{
		regist(6, &name_lable, &type_lable, &value_lable, &name_text, &type_text, &value_text);		
	}
	Modifier(NECodeKey::Trait& new_value)
		: Terminal("", NEType::NECODE_KEY, 20, 7, 40, 7, WHITE, BLACK),
		type_lable(0, 22, 10, 8, 1, WHITE, LIGHTRED, "Code Type:"),
		value_lable(0, 22, 12, 8, 1, WHITE, LIGHTRED, "Code:"),
		type_text(0, 30, 10, 8, 1, WHITE, BLACK),
		value_text(0, 30, 12, 8, 1, WHITE, BLACK),
		focused(1), real_key(0), value(new_value)
	{
		regist(4, &type_lable, &value_lable, &type_text, &value_text);
		type_text.text = createCodeTypeString(value.getCodeType());
		value_text.text = NEString(value.getCode());
	}
	Modifier(const Modifier& rhs)
		: Terminal(rhs), name_lable(rhs.name_lable), type_lable(rhs.type_lable), value_lable(rhs.value_lable),
		name_text(rhs.name_text), type_text(rhs.type_text), value_text(rhs.value_text), focused(rhs.focused),
		real_key(rhs.real_key), value(rhs.value)
	{
		regist(4, &type_lable, &value_lable, &type_text, &value_text);
		if(rhs.gliphs.getLength() > 4)
			regist(2, &name_lable, &name_text);
	}

	NEString createCodeTypeString(const NECodeType& type) const
	{
		switch(type.getCodeType())
		{
		case NECodeType::SCRIPT:	return "SCRIPT";
		case NECodeType::NAME:		return "NAME";
		case NECodeType::GROUP:		return "GROUP";
		case NECodeType::PRIORITY:	return "PRIORITY";
		case NECodeType::UNDEFINED:	return "UNDEFINED";
		case NECodeType::ME:		return "ME";
		case NECodeType::RECENT:	return "RECENT";
		case NECodeType::ALL:		return "ALL";
		}

		return "";
	}

	virtual void onFocused()
	{
		if (real_key)
			name_text.text = real_key->getName();
	}

	virtual void onUpdateData()
	{
		type_text.text = "<- " + createCodeTypeString(value.getCodeType()) + " ->";
		value_text.text = NEString(value.getCode());

		value_text.fore = type_text.fore = name_text.fore = BLACK;
		value_text.back = type_text.back = name_text.back = WHITE;		
		Gliph* f = 0;
		switch(focused) {
		case 0:	f = &name_text;		break;
		case 1: f = &type_text;		break;
		case 2: f = &value_text;	break;
		}
		if(f)
		{
			f->fore = LIGHTCYAN;
			f->back = CYAN;
		}	
	}
	virtual void onKeyPressed(char inputed)
	{
		switch (inputed)
		{
		case UP:
			if(focused > 0)
				focused--;
			if (!focused	&&
				!real_key)
				focused = 1;
			break;

		case DOWN:
			if (focused < 2)
				focused++;
			break;

		case LEFT:
			if (focused == 1)
			{
				int n = value.getCodeType();
				if (n > NECodeType::UNDEFINED)
					n--;
				if (n > 0)
					value.setCodeType(NECodeType::CodeType(n));
				else if (n == 0)
				{
					int c = value.getCode();
					value.release();
					value.setCode(c);
				}

			}
			break;

		case RIGHT:
			if (focused == 1)
			{
				int n = value.getCodeType();
				if (n < NECodeType::ALL)
					n++;
				value.setCodeType(NECodeType::CodeType(n));
			}
			break;

		case CONFIRM:
			switch (focused) {
		case 0:
			if (real_key)
				call(NameInputWindow(real_key->getName()));
			break;

		case 2:
			class CodeInputer : public LG::InputWindow
			{
			public:
				FUNC_TO_CALLER(Modifier<NECodeKey>)
					virtual NEObject& clone() const { return *(new CodeInputer(*this)); }
				CodeInputer() : LG::InputWindow("새로 추가할 CODE를 입력하세요.", BLACK, WHITE)
				{

				}

				virtual void onFocused()
				{
					NECode& value = toCaller().value;
					NEBank& bank = Editor::getInstance().getScriptEditor().getBanks().getBank(value);
					if (!&bank)
					{
						text = "뱅크를 가져오지 못했습니다. 에러";
						return;
					}

					NETString& name = bank[value.getCode()];
					if (!&name)
					{
						text = "잘못된 뱅크 인덱스입니다. 에러.";
						return;
					}

					input.history.release();
					for(NETStringList::Iterator* e = bank.getIterator(0); e; e = e->getNext())
						input.history.push(e->getValue());

					input.history_idx = value.getCode();
				}
				virtual void onUpdateData()
				{
					NEString& history = input.history[input.history_idx];
					if (&history)
						input.text = history;
				}

				virtual void onInputed()
				{
					NECode& value = toCaller().value;

					int code = input.text.toInt();
					value.setCode(code);

					delete_me = true;
				}
			};

			if (value.getCodeType() >= NECodeType::SCRIPT	&&
				value.getCodeType() <= NECodeType::PRIORITY)
				call(CodeInputer());

			}
			break;

		case CLOSE:
			delete_me = true;
			break;
		}		
	}	
	FUNC_CLONE(Modifier<NECodeKey>)

		NECodeKey::Trait& value;
	NECodeKey* real_key;
	Gliph name_lable, type_lable, value_lable, type_text, value_text;
	TextGliph name_text;
	int focused;
};


class Filter;

template <>
class Modifier<NENodeSelector> : public Window
{
public:
	Modifier();
	Modifier(const Modifier& rhs);

	class MenuList : public ListGliph
	{
	public:
		MenuList();
		FUNC_CLONE(MenuList);
		FUNC_TO_OWNER(Modifier<NENodeSelector>);

		NEString createNodeTypeStringFrom(NECodeType::CodeType type);
		const NETStringList& getProperBankFrom(NECodeType::CodeType type);
		void updateList();
		virtual void onUpdateData();

		virtual void onKeyPressed(char inputed);

		int codelist_display_index;
	};

	FUNC_CLONE(Modifier)
	FUNC_TO_CALLER(Filter)

	Gliph header, count_header, bind_header, code_type_header, use_and_header, peeking_lock_header, codelist_header;
	MenuList menulist;
};

template <>
class Modifier<NEModuleSelector> : public Window
{
public:
	Modifier()
		: Window(4, 17, 52, 8, LIGHTGRAY, DARKGRAY),
		bind_header		(0, 15, 18, 10, 1, WHITE, LIGHTRED, "ModuleBind?"),
		code_type_header(0, 15, 19, 10, 1, WHITE, LIGHTRED, "ModuleType"),
		codelist_header	(0, 15, 20, 10, 1, WHITE, LIGHTRED, "ModuleCodes")
	{
		regist(4, &bind_header, &code_type_header, &codelist_header, &menulist);
	}
	Modifier(const Modifier& rhs)
		: Window(rhs), bind_header(rhs.bind_header), code_type_header(rhs.code_type_header), 
		codelist_header(rhs.codelist_header), menulist(rhs.menulist)
	{
		regist(4, &bind_header, &code_type_header, &codelist_header, &menulist);
	}

	class MenuList : public ListGliph
	{
	public:
		MenuList() : ListGliph(0, 25, 18, 30, 6, BLACK, WHITE, WHITE, LIGHTRED), codelist_display_index(-1) {}
		FUNC_CLONE(MenuList)
			FUNC_TO_OWNER(Modifier<NEModuleSelector>)

			NEString createNodeTypeStringFrom(NECodeType::CodeType type)
		{
			switch(type)
			{
			case NECodeType::ME:		return "ME";
			case NECodeType::SCRIPT:	return "SCRIPT";
			case NECodeType::NAME:		return "NAME";
			case NECodeType::RECENT:	return "RECENT";
			case NECodeType::ALL:		return "ALL";
			default:					return "ERROR! UNKNOWN!";
			}
		}
		void updateList();
		const NETStringList& getProperBankFrom(NECodeType::CodeType type);
		virtual void onUpdateData()
		{
			if(items.getLength() < 3)
				updateList();

			for(int n=0; n < items.getLength() ;n++)
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

		virtual void onKeyPressed(char inputed);

		int codelist_display_index;
	};

	FUNC_CLONE(Modifier)
		FUNC_TO_CALLER(Filter)

		Gliph bind_header, code_type_header, use_and_header, codelist_header;
	MenuList menulist;
};

template <>
class Modifier<NEKeySelector> : public Window
{
public:
	Modifier()
		: Window(4, 17, 52, 8, LIGHTGRAY, DARKGRAY), 
		bind_header		(0, 15, 18, 10, 1, WHITE, LIGHTRED, "AutoBind?"),
		keyname_header	(0, 15, 19, 10, 1, WHITE, LIGHTRED, "KeyName")
	{
		regist(3, &bind_header, &keyname_header, &menulist);
	}
	Modifier(const Modifier& rhs)
		: Window(rhs), bind_header(rhs.bind_header), keyname_header(rhs.keyname_header), menulist(rhs.menulist)
	{
		regist(3, &bind_header, &keyname_header, &menulist);
	}

	class MenuList : public ListGliph
	{
	public:
		MenuList() : ListGliph(0, 25, 18, 30, 6, BLACK, WHITE, WHITE, LIGHTRED) {}
		FUNC_CLONE(MenuList)
			FUNC_TO_OWNER(Modifier<NEKeySelector>)

			void updateList();
		virtual void onUpdateData()
		{
			if(items.getLength() < 2)
				updateList();

			for(int n=0; n < 2 ;n++)
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

		virtual void onKeyPressed(char inputed);
	};

	FUNC_CLONE(Modifier)
	FUNC_TO_CALLER(Filter)

	Gliph bind_header, keyname_header;
	MenuList menulist;
};