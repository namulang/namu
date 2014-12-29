#pragma once

#include "../ModuleSetTerminal/ModuleSetTerminal.hpp"
#include "../KeySetTerminal/KeySetTerminal.hpp"

class NodeTerminal : public Terminal
{
public:
	class EnableSwitch : public LG::SwitchGliph
	{
	public: 
		EnableSwitch() : LG::SwitchGliph(0, 9, 4, 6, DARKGRAY, LIGHTCYAN) {}
		FUNC_CLONE(EnableSwitch)
		FUNC_TO_OWNER(NodeTerminal)

		virtual void onKeyPressed(char inputed)
		{
			LG::SwitchGliph::onKeyPressed(inputed);
			switch(inputed)
			{
			case LEFT:
			case RIGHT:
				toOwner()->castObject().setEnable(getValue());
				break;
			}
		}
	};
	virtual void onFocused()
	{
		enable.setValue(castObject().isEnable());
		enable.Gliph::back = CYAN;
		enable.Gliph::fore = LIGHTCYAN;
		attributes.choosed = -1;		
	}
	NodeTerminal(const NEString& new_path)	//	width : 70, height : 17 + 4 + 1(header) + space(1) = 23
		: Terminal(new_path, NEType::NENODE, 2, 3, 76, 18, WHITE, LIGHTGRAY),
		header(0, 2, 4, 76, 1, WHITE, DARKGRAY, ""),
		enable_header(0, 2, 4, 5, 1, DARKGRAY, LIGHTGRAY, "Enabl"),
		script_header(0, 2, 5, 5, 1, DARKGRAY, LIGHTGRAY, "Scr# "),
		script(0, 7, 5, 10, 1, DARKGRAY, LIGHTGRAY, ""),
		name_header(0, 2, 6, 5, 1, DARKGRAY, LIGHTGRAY, "Name "),
		group_header(0, 2, 7, 5, 1, DARKGRAY, LIGHTGRAY, "Group"),
		priority_header(0, 2, 8, 5, 1, DARKGRAY, LIGHTGRAY, "Prior"),
		ks_terminal(new_path+"/k", 17, 4), ms_terminal(new_path+"/m", 0, 48, 4), focused(0), codelist_display_index(-1)
	{
		regist(9, &header, &enable_header, &enable, &script_header, &script, &name_header, &group_header, &priority_header, &attributes);
	}
	NodeTerminal(const NodeTerminal& rhs)
		: Terminal(rhs), header(rhs.header), enable_header(rhs.enable_header), enable(rhs.enable), script_header(rhs.script_header), script(rhs.script), 
		name_header(rhs.name_header), group_header(rhs.group_header), priority_header(rhs.priority_header), ms_terminal(rhs.ms_terminal),
		ks_terminal(rhs.ks_terminal), focused(rhs.focused), codelist_display_index(rhs.codelist_display_index)
	{
		regist(9, &header, &enable_header, &enable, &script_header, &script, &name_header, &group_header, &priority_header, &attributes);
	}
	virtual void onUpdateData()
	{
		Terminal::onUpdateData();

		NENode& casted = castObject();
		if( ! &casted) return;
		NEScriptEditor::Banks& banks = Editor::getInstance().getScriptEditor().getBanks();

		script.text = banks.getBank(NECodeType::SCRIPT)[casted.getScriptCode()] + "[" + casted.getScriptCode() + "]";

		ks_terminal.onUpdateData();
		ms_terminal.onUpdateData();
	}
	virtual void onDraw()
	{
		LG::BackBuffer& buf = LG::Core::back_buffer;
		bool is_color_locked_already = buf.isColorLocked();

		if(focused != 0)
		{
			buf.setColor(BLACK, LIGHTGRAY);
			buf.setColorLock(true);
		}
		Terminal::onDraw();
		if( ! is_color_locked_already)
			buf.setColorLock(false);
		status.onDraw();

		if(focused != 1 && ! buf.isColorLocked())
		{
			buf.setColor(BLACK, DARKGRAY);
			buf.setColorLock(true);
		}
		ks_terminal.draw();

		if( ! is_color_locked_already)
			buf.setColorLock(false);

		if(focused != 2 && ! buf.isColorLocked())
		{
			buf.setColor(BLACK, DARKGRAY);
			buf.setColorLock(true);
		}
		ms_terminal.draw();
		
		if( ! is_color_locked_already)
			buf.setColorLock(false);
		_drawFrames();
	}
	virtual void onKeyPressed(char inputed);

	class Attributes : public ListGliph
	{
	public:
		FUNC_CLONE(Attributes)
		FUNC_TO_OWNER(NodeTerminal)

		Attributes() : ListGliph(0, 7, 6, 10, 3, BLACK, WHITE, CYAN, LIGHTCYAN)
		{

		}

		virtual void onUpdateData()
		{
			NENode& node = toOwner()->castObject();
			if( ! &node) return;

			NEScriptEditor::Banks& banks = Editor::getInstance().getScriptEditor().getBanks();
			items.create(3);
			_pushItemWith(banks.getBank(NECodeType::NAME), node.getNameCode());
			
			//_pushItemWith(banks.getBank(NECodeType::GROUP), node.getGroupCodes());
			const NETStringList& bank = Editor::getInstance().getScriptEditor().getBanks().getBank(NECodeType::GROUP);
			NEString codes_to_str;
			const NECodeSet& c = toOwner()->castObject().getGroupCodes();
			if( ! &bank)
				toOwner()->codelist_display_index = -1;
			switch(toOwner()->codelist_display_index)
			{
			case -2:	
				codes_to_str = "NEW";	break;
			case -1:	
				if( &bank)		
					codes_to_str = NEString(toOwner()->castObject().getGroupCodes().getLength()) + NEString(" codes");
				break;

			default:
				codes_to_str = bank[c[toOwner()->codelist_display_index].getCode()] + "[" + c[toOwner()->codelist_display_index].getCode() + "]";
				break;
			}

			items.push(codes_to_str);

			_pushItemWith(banks.getBank(NECodeType::PRIORITY), node.getPriorityCode());

			NEString& item = items[choosed];
			if( &item)
				item = "<- " + item + " ->";
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
						case NECodeType::SCRIPT:	return banks.getBank(NECodeType::SCRIPT);
						case NECodeType::NAME:		return banks.getBank(NECodeType::NAME);
						case NECodeType::GROUP:		return banks.getBank(NECodeType::GROUP);
						case NECodeType::PRIORITY:	return banks.getBank(NECodeType::PRIORITY);
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

					virtual void onFocused()
					{
						NECodeType::CodeType type = getTypeFromAttributesList();

						const NETStringList& bank = getProperBankFrom(type);

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
								NECodeSet cs = node.getGroupCodes();
								cs.resize(cs.getLength() + 1);
								cs.push(NECode(input.history_idx));
								node.setGroupCodes(cs);
							}
							break;

						case NECodeType::PRIORITY:
							node.setPriorityCode(input.history_idx);
							break;
						}

						toCaller().attributes.onUpdateData();

						delete_me = true;
					}
				};
				if(choosed == 1 && toOwner()->codelist_display_index >= 0)
				{
					NENode& node = toOwner()->castObject();
					NECodeSet cs = node.getGroupCodes();
					cs.remove(toOwner()->codelist_display_index);					
					cs.resize(cs.getLength());
					node.setGroupCodes(cs);		
					toOwner()->codelist_display_index = toOwner()->codelist_display_index > cs.getLengthLastIndex() ? cs.getLengthLastIndex() : toOwner()->codelist_display_index;
					onUpdateData();
				}
				else
					toOwner()->call(CodeInputer());
			}
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

	Gliph header, enable_header, script_header, script, name_header, group_header, priority_header;
	EnableSwitch enable;
	Attributes attributes;
	ModuleSetTerminal ms_terminal;
	KeySetTerminal ks_terminal;
	int focused;
	int codelist_display_index;
};