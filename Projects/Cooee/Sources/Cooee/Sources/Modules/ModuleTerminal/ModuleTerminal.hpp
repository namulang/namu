#pragma once

#include "../Terminal/Terminal.hpp"

class ModuleTerminal : public Terminal
{
public:
	class Header : public Gliph
	{
	public:
		Header() : Gliph(0, 5, 5, 70, 1, BLACK, LIGHTCYAN, "\t\t\t\t\t\t\t\tModule") {}		
	};
	class ModulePanel : public Gliph 
	{
	public:
		ModulePanel() : Gliph(0, 5, 6, 35, 3, WHITE, LIGHTRED) {}
		ModulePanel(const ModulePanel& rhs) : Gliph(rhs) {}
		FUNC_TO_OWNER(ModuleTerminal)
		FUNC_CLONE(ModulePanel)	

		virtual void onUpdateData();
	};
	class ContentPanel : public Gliph
	{
	public:
		ContentPanel() : Gliph(0, 5, 9, 35, 10, BLACK, WHITE) {}
		ContentPanel(const ContentPanel& rhs) : Gliph(rhs) {}
		FUNC_CLONE(ContentPanel)
		FUNC_TO_OWNER(ModuleTerminal)
		virtual void onUpdateData()
		{
			const NEExportable::ModuleHeader& header = toOwner()->castObject().getHeader();
			text = header.getComment();
		}
	};

	class ArgumentHeader : public Gliph
	{
	public:
		ArgumentHeader()
			: Gliph(0, 40, 6, 35, 2, BLACK, LIGHTMAGENTA,
			"KeyName			KeyType\n"
			"========================================") {}
		ArgumentHeader(const Header& rhs)
			: Gliph(rhs) {}
		FUNC_CLONE(ArgumentHeader)
		FUNC_TO_OWNER(ModuleTerminal)
	};

	class ArgumentNameList : public ListGliph
	{
	public:
		ArgumentNameList() : ListGliph(0, 40, 8, 17, 11, LIGHTRED, RED, WHITE, LIGHTRED) {}
		FUNC_TO_OWNER(ModuleTerminal)
		FUNC_CLONE(ArgumentNameList)
		virtual void onUpdateData()
		{
			const NEModule& m = toOwner()->castObject();			
			if( ! &m) return;
			const NEArgumentSet& args = m.getArguments();

			items.create(args.getLength());
			for(int n=0; n < args.getLength() ;n++)
				items.push(args[n].getKeyName());
		}
		virtual void onKeyPressed(char inputed);

	private:
		NENode& _getOwnerNodeOf(NEModule& target);
	};
	class ArgumentTypeList : public ListGliph
	{
	public:
		ArgumentTypeList() : ListGliph(0, 57, 8, 17, 11, BLACK, WHITE, WHITE, LIGHTRED) {}
		FUNC_TO_OWNER(ModuleTerminal)
		FUNC_CLONE(ArgumentTypeList)
		virtual void onUpdateData()
		{
			const NEModule& m = toOwner()->castObject();			
			if( ! &m) return;
			const NEArgumentSet& args = m.getArguments();

			items.create(args.getLength());
			for(int n=0; n < args.getLength() ;n++)
				items.push(NEType::getTypeName(args[n].getTypeToBeBinded()));
		}
	};

	ModuleTerminal(const NEString& new_path)
		: Terminal(new_path, NEType::NEMODULE, 4, 4, 72, 16, BLACK, CYAN)
	{
		regist(6, &header, &module_panel, &content_panel, &argument_header, &argument_namelist, &argument_typelist);
	}

	ModuleTerminal(const ModuleTerminal& rhs)
		: Terminal(rhs), header(rhs.header), module_panel(rhs.module_panel), content_panel(rhs.content_panel),
		argument_header(rhs.argument_header), argument_namelist(rhs.argument_namelist), argument_typelist(rhs.argument_typelist)
	{
		regist(6, &header, &module_panel, &content_panel, &argument_header, &argument_namelist, &argument_typelist);
	}

	FUNC_CLONE(ModuleTerminal)

	NEModule& castObject()
	{
		return (NEModule&) *instance;
	}

	Header header;
	ModulePanel module_panel;
	ContentPanel content_panel;
	ArgumentHeader argument_header;
	ArgumentNameList argument_namelist;
	ArgumentTypeList argument_typelist;
};