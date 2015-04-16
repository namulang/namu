#pragma once

#include "../Terminal/Terminal.hpp"

class ModuleSetTerminal : public Terminal {
public:
	ModuleSetTerminal(const NEString& new_path, NEKey* new_real_key = 0, type_ushort x=20, type_ushort y=4)
		: Terminal(new_path, NEType::NEMODULE_CODESET, x, y, 30, 17, BLACK, DARKGRAY), real_key(new_real_key)
	{
		regist(3, &header, &namelist, &commentlist); 

		if( ! instance)	//	setObject를 실패했다면
		{
			to_chk_valid = NEType::NEMODULE_CODESET_KEY;
			_setObject();
		}

	}
	ModuleSetTerminal(const ModuleSetTerminal& rhs) 
		: Terminal(rhs), header(rhs.header), namelist(rhs.namelist), real_key(rhs.real_key)
	{ 
		regist(3, &header, &namelist, &commentlist);

		if( ! instance)	//	setObject를 실패했다면
		{
			to_chk_valid = NEType::NEMODULE_CODESET_KEY;
			_setObject();
		}
	}
	FUNC_CLONE(ModuleSetTerminal)

		NEModuleCodeSet& castObject() {
			if( ! instance)
			{
				NEModuleCodeSet* nullpointer = 0x00;
				return *nullpointer;
			}
			if(to_chk_valid == NEType::NEMODULE_CODESET)
				return (NEModuleCodeSet&) *instance;
			else
				return ((NEModuleCodeSetKey&) *instance).getValue();
	}
	class ModuleNameList : public ListGliph
	{
	public:
		ModuleNameList() : ListGliph(0, 10, 7, 11, 15, LIGHTCYAN, CYAN, CYAN, LIGHTCYAN) { use_sound = true; }
		ModuleNameList(const ModuleNameList& rhs) : ListGliph(rhs) {}
		FUNC_TO_OWNER(ModuleSetTerminal)
			FUNC_CLONE(ModuleNameList)

			virtual void onUpdateData() {

				ListGliph::onUpdateData();

				x = toOwner()->x;
				y = toOwner()->y + 1;

				const NEModuleCodeSet& ms = toOwner()->castObject();
				if( ! &ms) return;
				items.create(ms.getLength() + 1);
				if(toOwner()->real_key)
					items.push(NEString("키 이름 : "));

				for (int n = 0; n < ms.getLength(); n++)
					items.push(ms[n].getHeader().getName());

		}
		virtual void onKeyPressed(int inputed);
	};
	class ModuleCommentList : public ListGliph
	{
	public:
		ModuleCommentList() : ListGliph(0, 30, 7, 20, 15, BLACK, WHITE, CYAN, LIGHTCYAN) {}
		ModuleCommentList(const ModuleCommentList& rhs) : ListGliph(rhs) {}
		FUNC_TO_OWNER(ModuleSetTerminal)
			FUNC_CLONE(ModuleCommentList)

			virtual void onUpdateData() {

				ListGliph::onUpdateData();

				x = toOwner()->x + 10;
				y = toOwner()->y + 1;

				const NEModuleCodeSet& ms = toOwner()->castObject();
				if( ! &ms) return;
				items.create(ms.getLength() + 1);
				if(toOwner()->real_key)
					items.push(toOwner()->real_key->getName());

				NEBank& bank = Editor::getInstance().getScriptEditor().getBanks().getBank(NECodeType::MODULE_NAME);

				for (int n = 0; n < ms.getLength(); n++) {
					const NETString* caption_of_item = &ms[n].getHeader().getComment();

					if (&bank)
					{
						const NETString& name = bank[ms[n].getNameCode()];
						if (&name && name != "")
							caption_of_item = &name;
					}

					items.push(*caption_of_item);			
				}
		}
	};
	class ListHeader : public Gliph {
	public:
		ListHeader() : Gliph(0, 10, 5, 30, 1, DARKGRAY, LIGHTGRAY) {
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

	void sendCommand(const NEString& text);

	ListHeader header;
	ModuleNameList namelist;
	ModuleCommentList commentlist;
	NEKey* real_key;
};