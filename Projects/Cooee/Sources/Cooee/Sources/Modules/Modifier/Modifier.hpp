#pragma once

#include "../InputTerminal/InputTerminal.hpp"

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

	Gliph header, count_header, bind_header, code_type_header, use_and_header, codelist_header;
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
		virtual void onUpdateData()
		{
			if(items.getLength() < 3)
				updateList();

			for(int n=0; n < 3 ;n++)
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