#pragma once

#include "../ModuleSetTerminal/ModuleSetTerminal.hpp"
#include "../KeySetTerminal/KeySetTerminal.hpp"

class NodeTerminal : public Terminal
{
public:
	NodeTerminal(const NEString& new_path)	//	width : 70, height : 17 + 4 + 1(header) + space(1) = 23
		: Terminal(new_path, NEType::NENODE, 5, 1, 70, 23, BLACK, DARKGRAY),
		header(5, 1, 40, 1, WHITE, LIGHTRED, "							Node Terminal"),
		script_header(45, 1, 30, 1, WHITE, LIGHTBLUE),
		name_header(5, 2, 15, 1, WHITE, LIGHTRED, " Name :"),
		group_header(5, 3, 15, 1, WHITE, LIGHTRED, " Group :"),
		priority_header(5, 4, 15, 1, WHITE, LIGHTRED, " Priority :")
	{
		regist(6, &header, &script_header, &name_header, &group_header, &priority_header, &attributes);
	}
	NodeTerminal(const NodeTerminal& rhs)
		: Terminal(rhs), header(rhs.header), script_header(rhs.script_header), name_header(rhs.name_header),
		group_header(rhs.group_header), priority_header(rhs.priority_header)
	{
		regist(6, &header, &script_header, &name_header, &group_header, &priority_header, &attributes);
	}

	virtual void onUpdateData()
	{
		NENode& casted = castObject();
		if( ! &casted) return;
		NEScriptEditor::Banks& banks = Editor::getInstance().getScriptEditor().getBanks();

		script_header.text = banks.getScriptBank()[casted.getScriptCode()] + "[" + casted.getScriptCode() + "]";
	}

	class Attributes : public ListGliph
	{
	public:
		FUNC_CLONE(Attributes)
		FUNC_TO_OWNER(NodeTerminal)

		Attributes() : ListGliph(0, 45, 2, 55, 3, BLACK, WHITE, WHITE, LIGHTRED)
		{

		}

		virtual void onUpdateData()
		{
			NENode& node = toOwner()->castObject();
			if( ! &node) return;

			NEScriptEditor::Banks& banks = Editor::getInstance().getScriptEditor().getBanks();
			items.create(3);
			_pushItemWith(banks.getNameBank(), node.getNameCode());
			_pushItemWith(banks.getGroupBank(), node.getGroupCode());
			_pushItemWith(banks.getPriorityBank(), node.getPriority());
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

	Gliph header, script_header, name_header, group_header, priority_header;
	Attributes attributes;
	ModuleSetTerminal ms_terminal;
	KeySetTerminal ks_terminal;
	
};