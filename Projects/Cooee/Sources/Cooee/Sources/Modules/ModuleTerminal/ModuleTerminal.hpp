#pragma once

#include "../Terminal/Terminal.hpp"

class ModuleTerminal : public Terminal
{
public:

	class FloatingPanel : public LG::FloatingGliph
	{
	public:
		FUNC_CLONE(FloatingPanel)
		FUNC_TO_OWNER(ModuleTerminal)

		FloatingPanel();

		virtual void onUpdateData()
		{
			int focused_arg_idx = toOwner()->argument_namelist.choosed,
				focused_item_y = toOwner()->argument_namelist.y + focused_arg_idx;
			x = 15;
			y = focused_item_y + 3;

			const NETStringSet& arg_comments = toOwner()->castObject().getHeader().getArgumentsComments();

			if(focused_arg_idx < 0 || focused_arg_idx > arg_comments.getLengthLastIndex())
				return;

			text = NEString("Argument ") + focused_arg_idx + " : " + arg_comments[focused_arg_idx];
		}
	};

	class ModulePanel : public Gliph 
	{
	public:
		ModulePanel() : Gliph(0, 4, 5, 35, 2, CYAN, LIGHTCYAN) {}
		ModulePanel(const ModulePanel& rhs) : Gliph(rhs) {}
		FUNC_TO_OWNER(ModuleTerminal)
		FUNC_CLONE(ModulePanel)	

		virtual void onUpdateData();
	};
	class ContentPanel : public Gliph
	{
	public:
		ContentPanel() : Gliph(0, 4, 7, 35, 12, LIGHTCYAN, CYAN) {}
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
			: Gliph(0, 39, 5, 37, 1, DARKGRAY, LIGHTGRAY,
			"KeyName			KeyType") {}
		ArgumentHeader(const ArgumentHeader& rhs)
			: Gliph(rhs) {}
		FUNC_CLONE(ArgumentHeader)
		FUNC_TO_OWNER(ModuleTerminal)
	};

	class ArgumentNameList : public ListGliph
	{
	public:
		ArgumentNameList() : ListGliph(0, 39, 6, 17, 12, LIGHTCYAN, CYAN, CYAN, LIGHTCYAN) {}
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
		ArgumentTypeList() : ListGliph(0, 56, 6, 20, 13, BLACK, WHITE, CYAN, LIGHTCYAN) {}
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
		regist(6, &module_panel, &content_panel, &argument_header, &argument_namelist, &argument_typelist, &argument_panel);
	}

	ModuleTerminal(const ModuleTerminal& rhs)
		: Terminal(rhs), argument_panel(rhs.argument_panel), module_panel(rhs.module_panel), content_panel(rhs.content_panel),
		argument_header(rhs.argument_header), argument_namelist(rhs.argument_namelist), argument_typelist(rhs.argument_typelist)
	{
		regist(6, &module_panel, &content_panel, &argument_header, &argument_namelist, &argument_typelist, &argument_panel);
	}

	FUNC_CLONE(ModuleTerminal)

	NEModule& castObject()
	{
		return (NEModule&) *instance;
	}

	FloatingPanel argument_panel;
	ModulePanel module_panel;
	ContentPanel content_panel;
	ArgumentHeader argument_header;
	ArgumentNameList argument_namelist;
	ArgumentTypeList argument_typelist;
};