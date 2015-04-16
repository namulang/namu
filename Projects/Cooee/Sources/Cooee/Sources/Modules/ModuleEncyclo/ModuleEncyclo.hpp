#pragma once

#include "../Core/Core.hpp"

class ModuleEncyclo : public Window
{
	class Status : public LG::Gliph {
	public:
		Status() : Gliph(0, 1, 1, 78, 1, LG::BLACK, LG::RED) {
			text = " > Module Enyclopedia!";
		}
		Status(const Status& rhs) : LG::Gliph(rhs) {}
		FUNC_CLONE(Status)
	};

	class ModulePanel : public Gliph 
	{
	public:
		ModulePanel() : Gliph(0, 22, 2, 57, 5, WHITE, LIGHTRED) {}
		ModulePanel(const ModulePanel& rhs) : Gliph(rhs) {}
		FUNC_TO_OWNER(ModuleEncyclo)
		FUNC_CLONE(ModulePanel)	
	};
	class ContentPanel : public Gliph
	{
	public:
		ContentPanel() : Gliph(0, 22, 7, 57, 17, BLACK, WHITE) {}
		ContentPanel(const ContentPanel& rhs) : Gliph(rhs) {}
		FUNC_CLONE(ContentPanel)
	};
	class ModuleList : public ListGliph
	{
	public:
		ModuleList(NEModule* new_want_to_browse = 0) 
			: ListGliph(0, 1, 2, 20, 22, BLACK, WHITE, WHITE, LIGHTRED, true), 
			want_to_browse(new_want_to_browse) {}
		ModuleList(const ModuleList& rhs) : ListGliph(rhs), want_to_browse(rhs.want_to_browse) { }
		FUNC_TO_OWNER(ModuleEncyclo)
		FUNC_CLONE(ModuleList)

		virtual void onUpdateData();
		NEString createModulePanelText(const NEModule& target);		
		void setPanelsTextByChoosed();
		virtual void onKeyPressed(int inputed);
		void _focusWhatWantToBrowse();
		NEModule* want_to_browse;
	};

public:
	ModuleEncyclo(NEModule* want_to_browse = 0, const NEString& new_path_to_added = "") 
		: Window(1, 1, 78, 23, BLACK, DARKGRAY), list(want_to_browse), path_to_added(new_path_to_added)
	{ 
		regist(4, &status, &panel, &content, &list);
	}
	ModuleEncyclo(CONST ModuleEncyclo & rhs) 
		: Window(rhs), list(rhs.list), content(rhs.content), panel(rhs.panel), path_to_added(rhs.path_to_added)
	{ 
		regist(4, &status, &panel, &content, &list);
	}
	NEObject& clone() const { return *(new ModuleEncyclo(*this)); }
	bool isAddingMode() const { return path_to_added != ""; }

	Status status;
	ModulePanel panel;
	ModuleList list;
	ContentPanel content;
	NEString path_to_added;
};