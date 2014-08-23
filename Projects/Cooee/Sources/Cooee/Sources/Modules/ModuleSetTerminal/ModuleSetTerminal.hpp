#pragma once

#include "../Terminal/Terminal.hpp"
#include "../BaseNavigator/BaseNavigator.hpp"

class ModuleSetTerminal : public Terminal {
public:
	ModuleSetTerminal(const NEString& new_path, NEKey* new_real_key = 0, type_ushort x=20, type_ushort y=4)
		: Terminal(new_path, NEType::NEMODULE_CODESET, x, y, 30, 17, BLACK, DARKGRAY), real_key(new_real_key)
	{
		regist(6, &header, &namelist, &commentlist, &navigator, &colon, &gate); 
		navigator.text = path; 
		if( ! instance)	//	setObject를 실패했다면
		{
			to_chk_valid = NEType::NEMODULE_CODESET_KEY;
			_setObject();
		}

	}
	ModuleSetTerminal(const ModuleSetTerminal& rhs) 
		: Terminal(rhs), header(rhs.header), namelist(rhs.namelist), navigator(rhs.navigator), colon(rhs.colon), 
		gate(rhs.gate), real_key(rhs.real_key)
	{ 
		regist(6, &header, &namelist, &commentlist, &navigator, &colon, &gate);
		navigator.text = path;
		
		if( ! instance)	//	setObject를 실패했다면
		{
			to_chk_valid = NEType::NEMODULE_CODESET_KEY;
			_setObject();
		}
	}
	FUNC_CLONE(ModuleSetTerminal)

	NEModuleCodeSet& castObject() {
		if(to_chk_valid == NEType::NEMODULE_CODESET)
			return (NEModuleCodeSet&) *instance;
		else
			return ((NEModuleCodeSetKey&) *instance).getValue();
	}
	class ModuleNameList : public ListGliph
	{
	public:
		ModuleNameList() : ListGliph(0, 10, 7, 10, 14, BLACK, RED, WHITE, LIGHTRED) {}
		ModuleNameList(const ModuleNameList& rhs) : ListGliph(rhs) {}
		FUNC_TO_OWNER(ModuleSetTerminal)
		FUNC_CLONE(ModuleNameList)

		virtual void onUpdateData() {

			x = toOwner()->x;
			y = toOwner()->y + 2;

			const NEModuleCodeSet& ms = toOwner()->castObject();
			if( ! &ms) return;
			items.create(ms.getLength() + 1);
			if(toOwner()->real_key)
				items.push(NEString("키 이름 : "));
			for(int n=0; n < ms.getLength() ;n++)
				items.push(ms[n].getHeader().getName());

			onDraw();
		}
		virtual void onKeyPressed(char inputed);
	};
	class ModuleCommentList : public ListGliph
	{
	public:
		ModuleCommentList() : ListGliph(0, 30, 7, 20, 14, BLACK, WHITE, WHITE, LIGHTRED) {}
		ModuleCommentList(const ModuleCommentList& rhs) : ListGliph(rhs) {}
		FUNC_TO_OWNER(ModuleSetTerminal)
		FUNC_CLONE(ModuleCommentList)

		virtual void onUpdateData() {

			x = toOwner()->x + 10;
			y = toOwner()->y + 2;

			const NEModuleCodeSet& ms = toOwner()->castObject();
			if( ! &ms) return;
			items.create(ms.getLength() + 1);
			if(toOwner()->real_key)
				items.push(toOwner()->real_key->getName());
			for(int n=0; n < ms.getLength() ;n++)
				items.push(ms[n].getHeader().getComment());

			onDraw();
		}
		virtual void onKeyPressed(char inputed)
		{
			ListGliph::onKeyPressed(inputed);

			if(inputed == UP || inputed == DOWN)
				onDraw();
		}
	};
	class ListHeader : public Gliph {
	public:
		ListHeader() : Gliph(0, 10, 5, 30, 2, BLACK, LIGHTCYAN) {
			text = 
				"Mod.Name	Comment\n"
				"========================================";
		}
		ListHeader(const ListHeader& rhs) : Gliph(rhs) {}
		FUNC_CLONE(ListHeader)
		FUNC_TO_OWNER(ModuleSetTerminal)

		virtual void onUpdateData()
		{
			x = toOwner()->x;
			y = toOwner()->y;
		}
	};

	class Navigator : public BaseNavigator {
	public:
		Navigator() : BaseNavigator("ModuelSet", 10, 20, 17, 1, BLACK, WHITE) {}
		Navigator(const Navigator& rhs) : BaseNavigator(rhs) {}
		FUNC_CLONE(Navigator)
		FUNC_TO_OWNER(ModuleSetTerminal)		
		virtual void onUpdateData()
		{
			x = toOwner()->x;
			y = toOwner()->y + 16;
		}
	};
	class Colon : public Gliph {
	public:
		Colon() : Gliph(0, 52, 20, 3, 1, WHITE, LIGHTRED) 
		{ 
			text = " > ";
		}
		Colon(const Colon& rhs) : Gliph(rhs) {}
		FUNC_CLONE(Colon)
		FUNC_TO_OWNER(ModuleSetTerminal)
		virtual void onUpdateData()
		{
			x = toOwner()->x + 17;
			y = toOwner()->y + 16;
		}
	};
	class GeniusGate : public TextGliph {
	public:
		GeniusGate() : TextGliph(0, 55, 20, 10, 1, WHITE, LIGHTRED), hinted(false) {}
		GeniusGate(const GeniusGate& rhs) : TextGliph(rhs), hinted(rhs.hinted) {}
		FUNC_CLONE(GeniusGate)
		FUNC_TO_OWNER(ModuleSetTerminal)
		virtual void onUpdateData()
		{
			x = toOwner()->x + 20;
			y = toOwner()->y + 16;
		}
		bool hinted;
	};

	void sendCommand(const NEString& text);

	ListHeader header;
	ModuleNameList namelist;
	ModuleCommentList commentlist;
	Navigator navigator;
	Colon colon;
	GeniusGate gate;
	NEKey* real_key;
};