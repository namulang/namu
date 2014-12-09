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
			if (focused_arg_idx < 0 || focused_arg_idx > toOwner()->argument_namelist.items.getLengthLastIndex())
				return;

			x = 15;
			y = focused_item_y + 3;

			const NETStringSet& arg_comments = toOwner()->castObject().getHeader().getArgumentsComments();

			if(focused_arg_idx < 0 || focused_arg_idx > arg_comments.getLengthLastIndex())
				return;

			NEStringKey arg_info("설명에 해당하는 Argument를 찾지 못했습니다.");
			NEModule& owner = toOwner()->castObject();
			if( ! &owner) return;
			NEArgumentBase& arg = owner.getArguments()[focused_arg_idx];
			if(&arg)
			{
				if(arg.isNeedingBinding())
				{
					arg_info = "지정한 Key : " + arg.getKeyName();

					NENode& node = toOwner()->getOwnerNodeOf(owner);
					if( ! &node) return;
					const NEKeyCodeSet& ks = node.getKeySet();
					for(int n=0; n < ks.getLength() ;n++)
						if(ks[n].getName() == arg.getKeyName())
							arg_info.getValue() += "[값: "+ NEStringKey(ks[n]).getValue() + "]";					
				}
				else	//	기본값만 출력:
				{
					arg_info = "키 대신 넣을 기본값 : \"" + NEStringKey(arg.getDefaultKey()).getValue() + "\"";
				}
			}

			text = arg_info.getValue() + "\n" + arg_comments[focused_arg_idx];
		}
	};

	class ModulePanel : public Gliph 
	{
	public:
		ModulePanel() : Gliph(0, 4, 3, 28, 2, CYAN, LIGHTCYAN) {}
		ModulePanel(const ModulePanel& rhs) : Gliph(rhs) {}
		FUNC_TO_OWNER(ModuleTerminal)
			FUNC_CLONE(ModulePanel)	

			virtual void onUpdateData();
	};
	class ContentPanel : public Gliph
	{
	public:
		ContentPanel() : Gliph(0, 4, 5, 28, 12, LIGHTCYAN, CYAN) {}
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
		ArgumentNameList() : ListGliph(0, 32, 6, 16, 12, LIGHTCYAN, CYAN, CYAN, LIGHTCYAN) {}
		FUNC_TO_OWNER(ModuleTerminal)
			FUNC_CLONE(ArgumentNameList)
			virtual void onUpdateData()
		{
			const NEModule& m = toOwner()->castObject();			
			if( ! &m) return;
			const NEArgumentSet& args = m.getArguments();

			items.create(args.getLength());
			for (int n = 0; n < args.getLength(); n++)
				items.push(args[n].getKeyName());
		}
		virtual void onKeyPressed(char inputed);		
	};
	class ArgumentTypeList : public ListGliph
	{
	public:
		ArgumentTypeList() : ListGliph(0, 60, 6, 16, 13, BLACK, WHITE, CYAN, LIGHTCYAN) {}
		FUNC_TO_OWNER(ModuleTerminal)
			FUNC_CLONE(ArgumentTypeList)
			virtual void onUpdateData()
		{
			const NEModule& m = toOwner()->castObject();			
			if( ! &m) return;
			const NEArgumentSet& args = m.getArguments();

			items.create(args.getLength());
			for (int n = 0; n < args.getLength(); n++)
			{
				const NEArgumentBase& arg = args[n];
				items.push(NEType::getTypeName(args[n].getTypeToBeBinded()));
			}
		}
		virtual void onKeyPressed(char inputed)
		{
			ListGliph::onKeyPressed(inputed);

			NEModule& m = toOwner()->castObject();
			if ( ! &m) return;
			NEArgumentBase& arg = m.getArguments()[choosed];
			if ( ! &arg) return;

			switch(inputed)
			{
			case LEFT:	arg.setEnable(false);	break;

			case RIGHT:	arg.setEnable(true);	break;
			}
		}
	};

	ModuleTerminal(const NEString& new_path)
		: Terminal(new_path, NEType::NEMODULE, 4, 3, 72, 18, BLACK, CYAN),
		enable_header(0, 39, 4, 37, 1, DARKGRAY, LIGHTGRAY, "Enable"),
		namecode_header(0, 39, 5, 17, 1, DARKGRAY, LIGHTGRAY, "Namecode"),
		enable_back(0, 56, 4, 20, 1, LIGHTGRAY, LIGHTGRAY)
	{
		regist(11, &module_panel, &content_panel, &argument_header, &argument_namelist, &argument_typelist, &argument_panel,
			&enable_header, &enable_back, &enable, &namecode_header, &namecode);

		enable.Gliph::back = CYAN;
		enable.Gliph::fore = LIGHTCYAN;
		argument_namelist.choosed = argument_typelist.choosed = -1;
	}

	ModuleTerminal(const ModuleTerminal& rhs)
		: Terminal(rhs), argument_panel(rhs.argument_panel), module_panel(rhs.module_panel), content_panel(rhs.content_panel),
		argument_header(rhs.argument_header), argument_namelist(rhs.argument_namelist), argument_typelist(rhs.argument_typelist),
		enable(rhs.enable), enable_header(rhs.enable_header), namecode_header(rhs.namecode_header), namecode(rhs.namecode),
		enable_back(rhs.enable_back)
	{
		regist(11, &module_panel, &content_panel, &argument_header, &argument_namelist, &argument_typelist, &argument_panel,
			&enable_header, &enable_back, &enable, &namecode_header, &namecode);

		enable.Gliph::back = CYAN;
		enable.Gliph::fore = LIGHTCYAN;
		argument_namelist.choosed = argument_typelist.choosed = -1;
	}

	FUNC_CLONE(ModuleTerminal)

	virtual void onFocused()
	{
		namecode.text = castObject().getNameCode();
		enable.setValue(castObject().isEnable());
		_createGears();
	}

	class MySwitch : public LG::SwitchGliph
	{
	public:
		MySwitch(NEArgumentBase& new_arg) 
			: SwitchGliph(0, 48, 6 + n, 12, LIGHTCYAN, WHITE), arg(new_arg)
		{

		};
		MySwitch(const MySwitch& rhs)
			: SwitchGliph(rhs), arg(rhs.arg) 
		{

		}

		virtual NEObject& clone() const
		{
			return *(new MySwitch(*this));
		}

		NEArgumentBase& arg;
	};
	class MyGear : public LG::GearGliph
	{
	public:
		MyGear(NEArgumentBase& new_arg, int y) 
			: GearGliph(0, 48, y, 12, LIGHTCYAN, WHITE), arg(new_arg)
		{

		};
		MyGear(const MyGear& rhs)
			: GearGliph(rhs), arg(rhs.arg) 
		{

		}

		virtual void onKeyPressed(char inputed)
		{
			GearGliph::onKeyPressed(inputed);

			switch(inputed)
			{
			case LEFT:
				if(getValue() < 0)

			case RIGHT:
			}
		}

		virtual NEObject& clone() const
		{
			return *(new MyGear(*this));
		}

		NEArgumentBase& arg;
	};

	void _createGears()
	{
		NEArgumentSet& args = castObject().getArguments();
		gears.create(args.getLength());
		for(int n=0; n < args.getLength() ;n++)
		{
			if(args[n].isOnlyForInput())
			{
				MySwitch sg(args[n], n);
				sg.setValue(args[n].isEnable());
				gears.push(sg);
			}
			else
			{
				MyGear gg(args[n], n);
				gg.setValue()
				gears.push();
			}
		}
	}

	virtual void onKeyPressed(char inputed)
	{
		switch (inputed)
		{
		case CANCEL:
		case CLOSE:
			Terminal::onKeyPressed(inputed);
			break;

		case UP:
			if (namecode.back == LIGHTCYAN)
			{
				namecode.back = WHITE;
				namecode.fore = BLACK;
				enable.Gliph::fore = LIGHTCYAN;
				enable.Gliph::back = CYAN;
				enable_back.back = WHITE;
			}
			else if (argument_typelist.choosed == 0)
			{
				argument_typelist.choosed = -1;
				argument_namelist.choosed = -1;
				namecode.back = LIGHTCYAN;
				namecode.fore = CYAN;
			}
			break;

		case DOWN:
			if (enable.Gliph::back == CYAN)
			{
				enable.Gliph::back = DARKGRAY;
				namecode.back = LIGHTCYAN;
				namecode.fore = CYAN;
				enable_back.back = LIGHTGRAY;
			}
			else if (namecode.back == LIGHTCYAN)
			{
				namecode.back = WHITE;
				namecode.fore = BLACK;			
			}
			break;
		}

		if (enable.Gliph::back == CYAN)
			enable.onKeyPressed(inputed);
		else if (namecode.back == LIGHTCYAN)
			namecode.onKeyPressed(inputed);
		else
		{
			argument_namelist.onKeyPressed(inputed);
			argument_typelist.onKeyPressed(inputed);
			argument_panel.onKeyPressed(inputed);
			module_panel.onKeyPressed(inputed);
			content_panel.onKeyPressed(inputed);
		}
	}

	NEModule& castObject()
	{
		return (NEModule&) *instance;
	}

	NENode& getOwnerNodeOf(NEModule& target);

	class EnableSwitch : public LG::SwitchGliph
	{
	public:
		EnableSwitch() : LG::SwitchGliph(0, 62, 4, 8, DARKGRAY, LIGHTCYAN) {}
		FUNC_CLONE(EnableSwitch)
		FUNC_TO_OWNER(ModuleTerminal)

		virtual void onKeyPressed(char inputed)
		{
			LG::SwitchGliph::onKeyPressed(inputed);
			switch (inputed)
			{
			case LEFT:
			case RIGHT:
				toOwner()->castObject().setEnable(getValue());
				break;
			}
		}
	};

	class NameGliph : public LG::Gliph
	{
	public:
		NameGliph() : LG::Gliph(0, 56, 5, 15, 1, CYAN, LIGHTCYAN, "") {}
		FUNC_TO_OWNER(ModuleTerminal)
			virtual void onKeyPressed(char inputed)
		{
			class CodeInputer : public LG::InputWindow
			{
			public:
				FUNC_TO_CALLER(ModuleTerminal)
					virtual NEObject& clone() const { return *(new CodeInputer(*this)); }
				CodeInputer() : LG::InputWindow("새로운 Name Code를 숫자로 입력하세요.\n자동으로 관리되지 않기에, 중복이 되지않도록 신경쓰세요.", BLACK, WHITE)
				{

				}

				virtual void onFocused()
				{
					input.text = NEString(toCaller().castObject().getNameCode());
				}				
				virtual void onInputed()
				{
					toCaller().castObject().setNameCode(input.text.toInt());

					delete_me = true;
				}
			};

			switch (inputed)
			{
			case CONFIRM:
				toOwner()->call(CodeInputer());
			}
		}
	};

	EnableSwitch enable;
	Gliph	enable_header,
			namecode_header,
			enable_back;
	NEArrayTemplate<Gliph*, true> gears;
	NameGliph namecode;
	FloatingPanel argument_panel;
	ModulePanel module_panel;
	ContentPanel content_panel;
	ArgumentHeader argument_header;
	ArgumentNameList argument_namelist;
	ArgumentTypeList argument_typelist;
};