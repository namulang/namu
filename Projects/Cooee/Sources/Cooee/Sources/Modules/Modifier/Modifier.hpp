#pragma once

#include "../InputTerminal/InputTerminal.hpp"

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
	Modifier(NEBooleanKey& key) 
		: Terminal("", NEType::NEBOOLEAN_KEY, 30, 10, 20, 5, WHITE, BLACK),
		sw(0, 38, 13, 4, LIGHTRED, WHITE), value(key.getValue())
	{
		regist(1, &sw);
	}
	Modifier(NEBooleanKey::Trait& new_value) 
		: Terminal("", NEType::NEBOOLEAN_KEY, 30, 10, 20, 5, WHITE, BLACK),
		sw(0, 38, 13, 4, LIGHTRED, WHITE), value(new_value)
	{
		regist(1, &sw);
	}

	Modifier(const Modifier& rhs) 
		: Terminal(rhs), sw(rhs.sw), value(rhs.value)
	{
		regist(1, &sw);
	}
				 
	virtual void onUpdateData()
	{
		sw.setValue(value);
	}

	void onKeyPressed(char inputed) 
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

	FUNC_CLONE(Modifier<NEBooleanKey>)

	LG::SwitchGliph sw;
	NEBooleanKey::Trait& value;
};

template <>
class Modifier<NENodeSelector> : public Window
{
public:
	class MenuList : public ListGliph
	{
	public:
		MenuList() : ListGliph(0, 1, 2, 18, 10, BLACK, WHITE, WHITE, LIGHTRED) {}
		FUNC_CLONE(MenuList)
		FUNC_TO_OWNER(Modifier<NENodeSelector>)

		virtual void onUpdateData()
		{
			items.create(5);
			NENodeSelector& k = toOwner()->key;
			if( ! &k) return;

			items.push(NEString("In:\t\t") + k.getManager().getTypeName());
			items.push(NEString("Count:\t") + k.getCountLimit());
			items.push(NEString("AutoBind:\t") + k.isUsingAutoBinding());
			NEString codes_to_str;
			const NEIntSet* c = &k.getCodeSet();
			for(int n=0; n < c->getLength() ;n++)
				codes_to_str += NEString(" ") + c->getElement(n);
			items.push(NEString("Code : ") + codes_to_str);
			items.push(NEString("And Oper. : ") + k.isUsingAndOperation());
		}

		class ManagerQuerier : public ::LG::ListWindow
		{
		public:
			ManagerQuerier() : ListWindow("어떤 영역의 Manager에서 검색할 것인가요?", 25, 9, 30, 7, WHITE, DARKGRAY) 
			{
				list.items.create(4);
				list.items.push("NodeManager");
				list.items.push("ScriptManager");
				list.items.push("ScriptEditor");
				list.items.push("PanelManager");
			}
			FUNC_CLONE(ManagerQuerier)
			FUNC_TO_OWNER(MenuList)

			virtual void onItemChoosed(type_index item_index, const NEString& chosen_content)
			{
				NENodeSelector& k = toOwner()->toOwner()->key;
				switch(item_index)
				{
				case 0:	k.setManager(NEType::NENODE_MANAGER);	break;
				case 1:	k.setManager(NEType::NESCRIPT_MANAGER);	break;
				case 2:	k.setManager(NEType::NESCRIPT_EDITOR);	break;
				case 3:	k.setManager(NEType::NEPANEL_MANAGER);	break;
				}

				toOwner()->toOwner()->tree.onUpdateData();

				delete_me = true;
			}
		};

		virtual void onKeyPressed(char inputed)
		{
			ListGliph::onKeyPressed(inputed);

			if(inputed == CONFIRM)
			{
				switch(choosed)
				{
				case 0:	//	MANAGER
					LG::Core::open(ManagerQuerier());
					break;
				case 1:	//	CountLimit
					break;
				case 2:	//	AutoBinding
					break;
				case 3:	//	Codes
					break;
				case 4:	//	AndOperation
					break;
				}
			}
		}
	};
	class CodeList : public ListGliph
	{
	public:
		CodeList() : ListGliph(0, 1, 13, 18, 10, BLACK, WHITE, WHITE, LIGHTRED) {}
		FUNC_CLONE(CodeList)
		FUNC_TO_OWNER(Modifier<NENodeSelector>)

		virtual void onUpdateData()
		{

		}
		virtual void onKeyPressed(char inputed)
		{

		}
	};
	class TreeList : public ListGliph
	{
	public:
		TreeList() : ListGliph(0, 20, 1, 59, 23, BLACK, WHITE, WHITE, LIGHTRED) {}
		FUNC_CLONE(TreeList)
		FUNC_TO_OWNER(Modifier<NENodeSelector>)

		virtual void onUpdateData()
		{

		}
		virtual void onKeyPressed(char inputed)
		{

		}
	};

	Modifier(NENodeSelector& new_key)
		: Window(0, 0, 80, 25, LIGHTGRAY, DARKGRAY),
		key(new_key) 
	{
	}
	Modifier(const Modifier& rhs)
		: Window(rhs), key(rhs.key)
	{
	}
	FUNC_CLONE(Modifier)

	virtual void onKeyPressed(char inputed)
	{
		switch(inputed)
		{
		case LEFT:
			if(focused_index > 0)
				focused_index--;
			break;
		case RIGHT:
			if(focused_index < 2)
				focused_index++;
			break;
		}

		_updateBackgroundColorOfList(inputed);
	}

	void _updateBackgroundColorOfList(char inputed)
	{
		menu.back = codes.back = tree.back = LIGHTGRAY;
		switch(focused_index)
		{
		case 0:
			menu.back = WHITE;
			menu.onKeyPressed(inputed);
			break;
		case 1:
			codes.back = WHITE;
			codes.onKeyPressed(inputed);
			break;
		case 2:
			tree.back = WHITE;
			tree.onKeyPressed(inputed);
		}
	}

	NENodeSelector& key;
	Gliph header, menu_header, code_header, tree_header;
	MenuList menu;
	CodeList codes;
	TreeList tree;
	MenuList::ManagerQuerier manager_querier;
	int focused_index;
};