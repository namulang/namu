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
		ModuleList(bool new_use_adding, NEModule* new_want_to_browse = 0) 
			: ListGliph(0, 1, 2, 20, 22, BLACK, WHITE, WHITE, LIGHTRED), 
			use_adding(new_use_adding), want_to_browse(new_want_to_browse) {}
		ModuleList(const ModuleList& rhs) : ListGliph(rhs), use_adding(rhs.use_adding), want_to_browse(rhs.want_to_browse) { }
		FUNC_TO_OWNER(ModuleEncyclo)
		FUNC_CLONE(ModuleList)

		virtual void onUpdateData() {
			const NEModuleSet& ms = Kernal::getInstance().getModuleManager().getModuleSet();
			items.create(ms.getLength());
			for(int n=0; n < ms.getLength() ;n++)
				items.push(ms[n].getHeader().getName());

			onDraw();
			_focusWhatWantToBrowse();
			setPanelsTextByChoosed();
			toOwner()->panel.onDraw();
			toOwner()->content.onDraw();
		}

		NEString createModulePanelText(const NEModule& target) 
		{
			const NEExportable::ModuleHeader& h = target.getHeader();
			return	"\n"
					"\t>\t" + h.getName() + "\n"
					"\t \tby " + h.getDeveloper() + " on " + h.getReleaseDate() + "\n"
					"\n";
		}
		void setPanelsTextByChoosed()
		{
			const NEModule& t = Kernal::getInstance().getModuleManager().getModuleSet()[choosed];
			if( ! &t)
			{
				toOwner()->content.text = "\n\tThere is no data to display";
				return;
			}

			toOwner()->panel.text = createModulePanelText(t);
			toOwner()->content.text = t.getHeader().getComment();
		}

		virtual void onKeyPressed(char inputed) {

			ListGliph::onKeyPressed(inputed);

			switch(inputed) {
			case UP:
			case DOWN:
				{
					setPanelsTextByChoosed();

					onDraw();
					toOwner()->panel.onDraw();
					toOwner()->content.onDraw();
				}
				break;
			case CONFIRM:
				if(use_adding) 
				{
					Core::commander.command("add ");
				}
				break;
			case CANCEL:
				toOwner()->delete_me = true;
			}
		}

		void _focusWhatWantToBrowse();
		bool use_adding;

		NEModule* want_to_browse;
	};

public:
	ModuleEncyclo(bool new_use_adding = false, NEModule* want_to_browse = 0) 
		: Window(1, 1, 78, 23, BLACK, DARKGRAY), list(new_use_adding, want_to_browse)
	{ 
		regist(4, &status, &panel, &list, &content);		
	}
	ModuleEncyclo(CONST ModuleEncyclo & rhs) : Window(rhs), list(rhs.list), content(rhs.content), panel(rhs.panel) { regist(4, &status, &panel, &list, &content); }
	NEObject& clone() const { return *(new ModuleEncyclo(*this)); }

	Status status;
	ModulePanel panel;
	ModuleList list;
	ContentPanel content;
};