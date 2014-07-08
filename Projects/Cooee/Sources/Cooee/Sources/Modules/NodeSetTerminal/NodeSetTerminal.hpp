#pragma once

#include "../Terminal/Terminal.hpp"
#include "../BaseNavigator/BaseNavigator.hpp"

class NodeSetTerminal : public Terminal {
public:
	NodeSetTerminal(const NEString& new_path = "/") 
		: Terminal(new_path, NEType::NENODE_CODESET, 1, 1, 78, 23, BLACK, DARKGRAY) 
	{ 
		regist(5, &header, &contents, &navigator, &colon, &gate);
		navigator.text = path;

		if( ! instance)	//	setObject를 실패했다면
		{
			to_chk_valid = NEType::NENODE_CODESET_KEY;
			_setObject();
		}
	}
	NodeSetTerminal(const NodeSetTerminal& rhs) 
		: Terminal(rhs), header(rhs.header), contents(rhs.contents), navigator(rhs.navigator), colon(rhs.colon), gate(rhs.gate)
	{ 
		regist(5, &header, &contents, &navigator, &colon, &gate);
		navigator.text = path;

		if( ! instance)	//	setObject를 실패했다면
		{
			to_chk_valid = NEType::NENODE_CODESET_KEY;
			_setObject();
		}
	}
	FUNC_CLONE(NodeSetTerminal)

	NENodeCodeSet& castObject() {
		if(to_chk_valid == NEType::NENODE_CODESET)
			return (NENodeCodeSet&) *instance;
		else
			return ((NENodeCodeSetKey&) *instance).getValue();
	}

	class ListHeader : public Gliph {
	public:
		ListHeader() : Gliph(0, 1, 2, 78, 2, BLACK, LIGHTGRAY) {
			text = 
				" Script#  Name or Contents                                 Module#  Key#\n"
				"==============================================================================";
		}
		ListHeader(const ListHeader& rhs) : Gliph(rhs) {}
		FUNC_CLONE(ListHeader)
		FUNC_TO_OWNER(NodeSetTerminal)
	};
	class ContentList : public ListGliph {
	public:
		ContentList() : ListGliph(0, 1, 4, 78, 19, BLACK, WHITE, WHITE, LIGHTRED) {}
		ContentList(const ContentList& rhs) : ListGliph(rhs) {}
		FUNC_CLONE(ContentList)
		FUNC_TO_OWNER(NodeSetTerminal)

		virtual void onKeyPressed(char inputed);
		NEString createCommand() const
		{
			NEStringSet splited;
			items[choosed].split(" ", splited);
			return "mv " + splited[0];
		}
		virtual void onUpdateData() {
			NENodeCodeSet& ns = toOwner()->castObject();
			if( ! &ns) return;
			items.create(ns.getLength());
			NETStringList& names = Editor::getInstance().getScriptEditor().getBanks().getScriptBank();
			for(int n=0; n < ns.getLength() ;n++) {
				NEString	s_idx = ns[n].getScriptCode(),
							name = names[s_idx.toInt()],
							m_cnt = ns[n].getModuleSet().getLength(),
							k_cnt = ns[n].getKeySet().getLength();
				makeStringFixed(s_idx, 8);
				makeStringFixed(name, 48);
				makeStringFixed(m_cnt, 8);
				makeStringFixed(k_cnt, 4);
				items.push(" " + s_idx + "  " + name + "  " + m_cnt + "  " + k_cnt);
			}
				
			onDraw();
		}

		void makeStringFixed(NEString& target_to_be_fixed, int to) {
			if(target_to_be_fixed.getLength() < to) {
				target_to_be_fixed.resize(to+1);
				while(target_to_be_fixed.getLength() < to)
					target_to_be_fixed.insert(target_to_be_fixed.getLengthLastIndex(), ' ');				
			} else if(target_to_be_fixed.getLength() > to) {
				target_to_be_fixed.resize(to + 1);
				target_to_be_fixed.setElement(target_to_be_fixed.getLengthLastIndex(), '\0');
			}
		}
	};
	class Navigator : public BaseNavigator {
	public:
		Navigator() : BaseNavigator("NodeSet", 3, 23, 52, 1, BLACK, WHITE) {			
		}
		Navigator(const Navigator& rhs) : BaseNavigator(rhs) {}
		FUNC_CLONE(Navigator)
		FUNC_TO_OWNER(NodeSetTerminal)
	};
	class Colon : public Gliph {
	public:
		Colon() : Gliph(0, 57, 23, 3, 1, WHITE, LIGHTRED) { text = " > ";}
		Colon(const Colon& rhs) : Gliph(rhs) {}
		FUNC_CLONE(Colon)
			FUNC_TO_OWNER(NodeSetTerminal)
	};
	class GeniusGate : public TextGliph {
	public:
		GeniusGate() : TextGliph(0, 60, 23, 19, 1, WHITE, LIGHTRED), hinted(false) {

		}
		GeniusGate(const GeniusGate& rhs) : TextGliph(rhs), hinted(rhs.hinted) {}
		FUNC_CLONE(GeniusGate)
			FUNC_TO_OWNER(NodeSetTerminal)
			bool hinted;

		virtual void onKeyPressed(char inputed);
	};

	ListHeader header;
	ContentList contents;
	Navigator navigator;
	Colon colon;
	GeniusGate gate;
};