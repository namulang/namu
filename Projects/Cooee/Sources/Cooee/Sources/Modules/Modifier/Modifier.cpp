#include "Modifier.hpp"

template <>
Modifier<NEBooleanKey>::Modifier(NEBooleanKey& key) 
	: Terminal("", NEType::NEBOOLEAN_KEY, 30, 10, 20, 5, WHITE, BLACK),
	sw(0, 38, 13, 4, LIGHTRED, WHITE), value(key.getValue())
{
	regist(1, &sw);
}
template <>
Modifier<NEBooleanKey>::Modifier(NEBooleanKey::Trait& new_value) 
	: Terminal("", NEType::NEBOOLEAN_KEY, 30, 10, 20, 5, WHITE, BLACK),
	sw(0, 38, 13, 4, LIGHTRED, WHITE), value(new_value)
{
	regist(1, &sw);
}

template <>
Modifier<NEBooleanKey>::Modifier(const Modifier& rhs) 
	: Terminal(rhs), sw(rhs.sw), value(rhs.value)
{
	regist(1, &sw);
}

template <>
void Modifier<NEBooleanKey>::onUpdateData()
{
	sw.setValue(value);
}

template <>
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


template <>
Modifier<NENodeSelector>::Modifier(NENodeSelector& new_key)
	: Window(4, 17, 52, 8, LIGHTGRAY, DARKGRAY), key(new_key),
	header			(0, 15, 18, 10, 1, WHITE, LIGHTRED, "Manager"),
	count_header	(0, 15, 19, 10, 1, WHITE, LIGHTRED, "Count"),
	bind_header		(0, 15, 20, 10, 1, WHITE, LIGHTRED, "Bind?"),
	code_type_header(0, 15, 21, 10, 1, WHITE, LIGHTRED, "NodeType"),
	use_and_header	(0,	15, 22, 10, 1, WHITE, LIGHTRED, "Use &&"),
	codelist_header	(0, 15, 23, 10, 1, WHITE, LIGHTRED, "Codes")
{
	regist(7, &header, &count_header, &bind_header, &code_type_header, &use_and_header, &codelist_header, &menulist);
}

template <>
Modifier<NENodeSelector>::Modifier(const Modifier& rhs)
	: Window(rhs), key(rhs.key), header(rhs.header), count_header(rhs.count_header), bind_header(rhs.bind_header), 
	code_type_header(rhs.code_type_header), use_and_header(rhs.use_and_header), codelist_header(rhs.codelist_header), 
	menulist(rhs.menulist)
{
	regist(7, &header, &count_header, &bind_header, &code_type_header, &use_and_header, &codelist_header, &menulist);
}

template <>
Modifier<NENodeSelector>::MenuList::MenuList() 
	: ListGliph(0, 25, 18, 30, 6, BLACK, WHITE, WHITE, LIGHTRED), codelist_display_index(-1) {}
template <>
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
template <>
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
template <>
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
template <>
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
template <>
void Modifier<NENodeSelector>::MenuList::onKeyPressed(char inputed)