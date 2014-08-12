#pragma once

#include "../InputTerminal/InputTerminal.hpp"
#include "../FilterModifier/FilterModifier.hpp"

template <typename KEY>
class Modifier : public InputTerminal
{
public:
	Modifier(KEY& key)
		: InputTerminal("", "주어진 키의 새로운 값을 입력하세요", KEY().getType()),
		value(key.getValue())
	{

	}
	Modifier(typename KEY::Trait& new_value)
		: InputTerminal("", "주어진 키의 새로운 값을 입력하세요", NEType::NEKEY), 
		value(new_value)
	{

	}
	Modifier(const Modifier& rhs) : InputTerminal(rhs), value(rhs.value) {}

	virtual void onUpdateData()
	{
		textbox.text = value;
	}

	virtual void onTextInputed()
	{		
		KEY temp(value);
		temp = NEStringKey(textbox.text);
		value = temp.getValue();
	}

	typename KEY::Trait& value;
	FUNC_CLONE(Modifier<KEY>)
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
	FUNC_CLONE(Modifier<NEBooleanKey>)

	LG::SwitchGliph sw;
	NEBooleanKey::Trait& value;
};

class Filter;

template <>
class Modifier<NENodeSelector> : public FilterModifier
{
public:
	Modifier(NENodeSelector& new_key);
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
	FUNC_TO_OWNER(Filter)

	NENodeSelector& key;
	Gliph header, count_header, bind_header, code_type_header, use_and_header, codelist_header;
	MenuList menulist;
};

template <>
class Modifier<NEModuleSelector> : public FilterModifier
{
public:
	Modifier(NEModuleSelector& new_key)
		: FilterModifier(4, 17, 52, 8, LIGHTGRAY, DARKGRAY), key(new_key),
		bind_header		(0, 15, 18, 10, 1, WHITE, LIGHTRED, "ModuleBind?"),
		code_type_header(0, 15, 19, 10, 1, WHITE, LIGHTRED, "ModuleType"),
		codelist_header	(0, 15, 20, 10, 1, WHITE, LIGHTRED, "ModuleCodes")
	{
		regist(4, &bind_header, &code_type_header, &codelist_header, &menulist);
	}
	Modifier(const Modifier& rhs)
		: FilterModifier(rhs), key(rhs.key), bind_header(rhs.bind_header), code_type_header(rhs.code_type_header), 
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
		void updateList()
		{
			NEModuleSelector& k = toOwner()->key;
			if( ! &k) return;

			items.create(3);
			items.push(NEString("   ") + k.isUsingAutoBinding());
			items.push(NEString("   ") + createNodeTypeStringFrom(k.getModuleType()));

			NEString codes_to_str;
			const NEIntSet& c = k.getModuleCodeSet();

			if(	k.getModuleType() == NECodeType::ALL	||
				k.getModuleType() == NECodeType::RECENT	||
				k.getModuleType() == NECodeType::ME		)
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
					for(int n=0; n < c.getLength() ;n++)
						codes_to_str += NEString(c[n]) + " ";
					break;

				default:
					codes_to_str = NEString("[") + codelist_display_index + "]" + c[codelist_display_index];
					break;
				}
			}

			items.push("   " + codes_to_str);
		}
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

	NEModuleSelector& key;
	Gliph bind_header, code_type_header, use_and_header, codelist_header;
	MenuList menulist;
};

template <>
class Modifier<NEKeySelector> : public FilterModifier
{
public:
	Modifier(NEKeySelector& new_key)
		: FilterModifier(4, 17, 52, 8, LIGHTGRAY, DARKGRAY), key(new_key),
		bind_header		(0, 15, 18, 10, 1, WHITE, LIGHTRED, "AutoBind?"),
		keyname_header	(0, 15, 19, 10, 1, WHITE, LIGHTRED, "KeyName")
	{
		regist(3, &bind_header, &keyname_header, &menulist);
	}
	Modifier(const Modifier& rhs)
		: FilterModifier(rhs), key(rhs.key), bind_header(rhs.bind_header), keyname_header(rhs.keyname_header), menulist(rhs.menulist)
	{
		regist(3, &bind_header, &keyname_header, &menulist);
	}

	class MenuList : public ListGliph
	{
	public:
		MenuList() : ListGliph(0, 25, 18, 30, 6, BLACK, WHITE, WHITE, LIGHTRED) {}
		FUNC_CLONE(MenuList)
		FUNC_TO_OWNER(Modifier<NEKeySelector>)

		void updateList()
		{
			NEKeySelector& k = toOwner()->key;
			if( ! &k) return;

			items.create(2);
			items.push(NEString("   ") + k.isUsingAutoBinding());
			items.push(NEString("   ") + k.getKeyName());
		}
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
					if(item.getLength() > 1 && item[item.getLengthLastIndex()-1] != '>')
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

		NEKeySelector& key;
	Gliph bind_header, keyname_header;
	MenuList menulist;
};