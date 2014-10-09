#pragma once

#include "../ModuleSetTerminal/ModuleSetTerminal.hpp"
#include "../KeySetTerminal/KeySetTerminal.hpp"

class NodeTerminal : public Terminal
{
public:
	NodeTerminal(const NEString& new_path)	//	width : 70, height : 17 + 4 + 1(header) + space(1) = 23
		: Terminal(new_path, NEType::NENODE, 2, 2, 76, 22, WHITE, LIGHTGRAY),
		header(0, 2, 3, 76, 1, WHITE, DARKGRAY, ""),
		script_header(0, 2, 5, 15, 3, WHITE, LIGHTBLUE),
		name_header(0, 2, 8, 5, 1, WHITE, LIGHTRED, "Name "),
		group_header(0, 2, 9, 9, 1, WHITE, LIGHTRED, "Group"),
		priority_header(0, 2, 10, 5, 1, WHITE, LIGHTRED, "Prior"),
		ks_terminal(new_path+"/k", 17, 5), ms_terminal(new_path+"/m", 0, 47, 5), focused(0), codelist_display_index(-1)
	{
		regist(6, &header, &script_header, &name_header, &group_header, &priority_header, &attributes);
	}
	NodeTerminal(const NodeTerminal& rhs)
		: Terminal(rhs), header(rhs.header), script_header(rhs.script_header), name_header(rhs.name_header),
		group_header(rhs.group_header), priority_header(rhs.priority_header), ms_terminal(rhs.ms_terminal),
		ks_terminal(rhs.ks_terminal), focused(rhs.focused), codelist_display_index(rhs.codelist_display_index)
	{
		regist(6, &header, &script_header, &name_header, &group_header, &priority_header, &attributes);
	}
	virtual void onUpdateData()
	{
		Terminal::onUpdateData();

		NENode& casted = castObject();
		if( ! &casted) return;
		NEScriptEditor::Banks& banks = Editor::getInstance().getScriptEditor().getBanks();

		script_header.text = NEString(" Base Stats\n===============") + 
			"Scr#: " + banks.getScriptBank()[casted.getScriptCode()] + "[" + casted.getScriptCode() + "]";

		ks_terminal.onUpdateData();
		ms_terminal.onUpdateData();
	}
	virtual void onDraw()
	{
		if(focused != 0)
		{
			LG::Core::setColor(BLACK, LIGHTGRAY);
			LG::Core::setColorLock(true);
		}
		Terminal::onDraw();
		LG::Core::setColorLock(false);

		if(focused != 1)
		{
			LG::Core::setColor(BLACK, DARKGRAY);
			LG::Core::setColorLock(true);
		}
		ks_terminal.draw();
		LG::Core::setColorLock(false);

		if(focused != 2)
		{
			LG::Core::setColor(BLACK, DARKGRAY);
			LG::Core::setColorLock(true);
		}
		ms_terminal.draw();
		LG::Core::setColorLock(false);
	}
	virtual void onKeyPressed(char inputed)
	{
		switch(inputed)
		{
		case CANCEL:
			delete_me = true;
			break;

		case LEFT:
			if(focused == 0 && attributes.choosed == 1)
			{
				if(codelist_display_index > -2)
					codelist_display_index--;
				attributes.onUpdateData();
				attributes.onDraw();
			}
			else if(focused > 0)
			{
				focused--;
				onUpdateData();
				onDraw();
			}
			break;

		case RIGHT:
			if(focused == 0 && attributes.choosed == 1)
			{
				if(codelist_display_index < castObject().getGroupCode().getLengthLastIndex())
					codelist_display_index++;
				attributes.onUpdateData();
				attributes.onDraw();
			} 
			else if(focused < 2)
			{
				focused++;
				onUpdateData();
				onDraw();
			}
			break;

		default:
			switch(focused)
			{
			case 0:
				Terminal::onKeyPressed(inputed);
				break;

			case 1:
				ks_terminal.onKeyPressed(inputed);
				break;

			case 2:
				ms_terminal.onKeyPressed(inputed);
				break;
			}
			break;
		}
	}

	class Attributes : public ListGliph
	{
	public:
		FUNC_CLONE(Attributes)
		FUNC_TO_OWNER(NodeTerminal)

		Attributes() : ListGliph(0, 7, 8, 10, 3, BLACK, WHITE, WHITE, LIGHTRED)
		{

		}

		virtual void onUpdateData()
		{
			NENode& node = toOwner()->castObject();
			if( ! &node) return;

			NEScriptEditor::Banks& banks = Editor::getInstance().getScriptEditor().getBanks();
			items.create(3);
			_pushItemWith(banks.getNameBank(), node.getNameCode());
			
			//_pushItemWith(banks.getGroupBank(), node.getGroupCode());
			const NETStringList& bank = Editor::getInstance().getScriptEditor().getBanks().getGroupBank();
			NEString codes_to_str;
			const NEIntSet& c = toOwner()->castObject().getGroupCode();
			if( ! &bank)
				toOwner()->codelist_display_index = -1;
			switch(toOwner()->codelist_display_index)
			{
			case -2:	codes_to_str = "NEW";	break;
			case -1:	
				if( &bank)		
					codes_to_str = NEString(toOwner()->castObject().getGroupCode().getLength()) + NEString(" codes");
				break;

			default:
				codes_to_str = NEString(toOwner()->codelist_display_index)+ "th: " + bank[c[toOwner()->codelist_display_index]] + "(" + c[toOwner()->codelist_display_index] + ")";
				break;
			}

			items.push("   " + codes_to_str);

			_pushItemWith(banks.getPriorityBank(), node.getPriority());
		}
		virtual void onKeyPressed(char inputed)
		{
			ListGliph::onKeyPressed(inputed);

			switch(inputed)
			{
			case CONFIRM:
				class CodeInputer : public LG::InputWindow
				{
				public:
					FUNC_TO_CALLER(NodeTerminal)
						virtual NEObject& clone() const { return *(new CodeInputer(*this)); }
					CodeInputer() : LG::InputWindow("새로 추가할 CODE를 좌우 방향키로 선택하세요", BLACK, WHITE) 
					{

					}

					const NETStringList& getProperBankFrom(NECodeType::CodeType type) const
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

					NECodeType::CodeType getTypeFromAttributesList()
					{
						switch(toCaller().attributes.choosed)
						{
						case 0:	return NECodeType::NAME;
						case 1:	return NECodeType::GROUP;
						case 2: return NECodeType::PRIORITY;
						}

						return NECodeType::UNDEFINED;
					}

					virtual void onUpdateData()
					{
						NECodeType::CodeType type = getTypeFromAttributesList();

						const NETStringList& bank = getProperBankFrom(type);

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
						case CONFIRM:
							inputed = ENTER;
							InputWindow::onKeyPressed(inputed);
							break;

						case CANCEL:
							inputed = CLOSE;
							InputWindow::onKeyPressed(inputed);
							break;

						case ENTER:
						case CLOSE:
						case LEFT:
						case RIGHT:
							InputWindow::onKeyPressed(inputed);
							break;
						}
					}

					virtual void onInputed()						
					{
						NENode& node = toCaller().castObject();
						switch(getTypeFromAttributesList())
						{
						case NECodeType::NAME:
							node.setNameCode(input.history_idx);
							break;

						case NECodeType::GROUP:
							{
								NECodeSet cs = node.getGroupCode();
								cs.resize(cs.getLength() + 1);
								cs.push(input.history_idx);
								node.setGroupCode(cs);
							}
							break;

						case NECodeType::PRIORITY:
							node.setPriority(input.history_idx);
							break;
						}

						toCaller().attributes.onUpdateData();
						toCaller().attributes.onDraw();

						delete_me = true;
					}
				};
				if(choosed == 1 && toOwner()->codelist_display_index >= 0)
				{
					NENode& node = toOwner()->castObject();
					NECodeSet cs = node.getGroupCode();
					cs.remove(toOwner()->codelist_display_index);					
					cs.resize(cs.getLength());
					node.setGroupCode(cs);		
					toOwner()->codelist_display_index = toOwner()->codelist_display_index > cs.getLengthLastIndex() ? cs.getLengthLastIndex() : toOwner()->codelist_display_index;
					onUpdateData();
				}
				else
					toOwner()->call(CodeInputer());
			}

			onDraw();
		}

		void _pushItemWith(const NETStringList& bank, const NEIntSet& groupcodes)
		{
			NEString to_pushed;
			for(int n=0; n < groupcodes.getLength(); n++)
			{
				int code = groupcodes[n];
				if(code < 0 || code > bank.getLengthLastIndex())
					to_pushed += NEString("Err(") + code + ")";

				to_pushed += bank[code] + "[" + code + "] ";
			}

			items.push(to_pushed);
		}
		void _pushItemWith(const NETStringList& bank, type_index index)
		{
			if(index < 0 || index > bank.getLengthLastIndex())
				items.push(NEString("out of index : ") + index);
			else
				items.push(bank[index] + "[" + index + "]");
		}
	};

	NENode& castObject()
	{
		return (NENode&) *instance;
	}

	FUNC_CLONE(NodeTerminal)

	Gliph header, script_header, name_header, group_header, priority_header;
	Attributes attributes;
	ModuleSetTerminal ms_terminal;
	KeySetTerminal ks_terminal;
	int focused;
	int codelist_display_index;
};