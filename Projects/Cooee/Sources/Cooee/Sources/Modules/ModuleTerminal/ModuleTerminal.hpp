#pragma once

#include "../Terminal/Terminal.hpp"

class ModuleTerminal : public Terminal
{
public:
	class GliphSet : public LG::Gliph
	{
	public:
		GliphSet() : Gliph(0, 0, 0, 0, 0, 0, 0) {}
		GliphSet(const GliphSet& rhs) : Gliph(rhs), arr(rhs.arr) {}
		virtual void onDraw()
		{
			for(int n=0; n < arr.getLength() ;n++)
				arr.getElement(n).onDraw();
		}
		virtual void onUpdateData()
		{
			for(int n=0; n < arr.getLength() ;n++)
				arr.getElement(n).onUpdateData();
		}
		virtual void onKeyPressed(char inputed)
		{
			for(int n=0; n < arr.getLength() ;n++)
				arr.getElement(n).onKeyPressed(inputed);
		}
		NEArrayTemplate<LG::Gliph*, true> arr;
	};

	class FloatingPanel : public LG::FloatingGliph
	{
	public:
		FUNC_CLONE(FloatingPanel)
			FUNC_TO_OWNER(ModuleTerminal)

			FloatingPanel();

		virtual void onUpdateData()
		{
			int focused_arg_idx = toOwner()->argument_namelist.choosed;
			Gliph& trg = toOwner()->gears.arr[focused_arg_idx];
			if( ! &trg) return;

			if(focused_arg_idx < 0 || focused_arg_idx > toOwner()->argument_namelist.items.getLengthLastIndex())
				return;

			x = 15;

			y = trg.y + 3;
			if(y + height >= 25)
				y = trg.y - 3 - height;

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
		ModulePanel() : Gliph(0, 4, 3, 26, 2, CYAN, LIGHTCYAN) {}
		ModulePanel(const ModulePanel& rhs) : Gliph(rhs) {}
		FUNC_TO_OWNER(ModuleTerminal)
			FUNC_CLONE(ModulePanel)	

			virtual void onUpdateData();
	};
	class ContentPanel : public Gliph
	{
	public:
		ContentPanel() : Gliph(0, 4, 5, 26, 15, LIGHTCYAN, CYAN) {}
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
			: Gliph(0, 30, 6, 45, 1, DARKGRAY, LIGHTGRAY,
			"KeyName\t\tDirection\t  KeyType") {}
		ArgumentHeader(const ArgumentHeader& rhs)
			: Gliph(rhs) {}
		FUNC_CLONE(ArgumentHeader)
			FUNC_TO_OWNER(ModuleTerminal)
	};

	class ArgumentNameList : public ListGliph
	{
	public:
		ArgumentNameList() : ListGliph(0, 30, 7, 15, 13, LIGHTCYAN, CYAN, CYAN, LIGHTCYAN) { use_sound = true; }
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
		ArgumentTypeList() : ListGliph(0, 60, 7, 15, 13, BLACK, WHITE, CYAN, LIGHTCYAN) {}
		FUNC_TO_OWNER(ModuleTerminal)
			FUNC_CLONE(ArgumentTypeList)
			virtual void onUpdateData()
		{
			const NEModule& m = toOwner()->castObject();			
			if( ! &m) return;
			const NEArgumentSet& args = m.getArguments();

			items.create(args.getLength());
			for (int n = 0; n < args.getLength(); n++)
				items.push(NEType::getTypeName(args[n].getTypeToBeBinded()));
		}
		virtual void onKeyPressed(char inputed)
		{
			ListGliph::onKeyPressed(inputed);			

			switch(inputed)
			{
			case LEFT:
			case RIGHT:	
				{
					Gliph& g = toOwner()->gears.arr[choosed];
					if( &g)
						g.onKeyPressed(inputed);
				}
				break;
			}
		}
	};

	ModuleTerminal(const NEString& new_path)
		: Terminal(new_path, NEType::NEMODULE, 4, 3, 72, 18, BLACK, DARKGRAY),
		enable_header(0, 30, 4, 30, 1, DARKGRAY, LIGHTGRAY, "\t\t\t\t\t\tEnable"),
		namecode_header(0, 30, 5, 30, 1, DARKGRAY, LIGHTGRAY, "\t\t\t\t\t  Namecode")
	{
		regist(11, &module_panel, &content_panel, &argument_header, &argument_namelist, &argument_typelist, &gears,
			&enable_header, &enable, &namecode_header, &namecode, &argument_panel);

		enable.Gliph::back = CYAN;
		enable.Gliph::fore = LIGHTCYAN;
		argument_namelist.choosed = argument_typelist.choosed = -1;
	}

	ModuleTerminal(const ModuleTerminal& rhs)
		: Terminal(rhs), argument_panel(rhs.argument_panel), module_panel(rhs.module_panel), content_panel(rhs.content_panel),
		argument_header(rhs.argument_header), argument_namelist(rhs.argument_namelist), argument_typelist(rhs.argument_typelist),
		enable(rhs.enable), enable_header(rhs.enable_header), namecode_header(rhs.namecode_header), namecode(rhs.namecode), gears(rhs.gears)	
	{
		regist(11, &module_panel, &content_panel, &argument_header, &argument_namelist, &argument_typelist, &gears,
			&enable_header, &enable, &namecode_header, &namecode, &argument_panel);

		enable.Gliph::back = CYAN;
		enable.Gliph::fore = LIGHTCYAN;
		argument_namelist.choosed = argument_typelist.choosed = -1;
	}

	FUNC_CLONE(ModuleTerminal)

		virtual void onFocused()
	{
		namecode.text = castObject().getNameCode();
		enable.setValue(castObject().isEnable());
		enable.text = enable.getValue() ? "------ON!------" : "------OFF-------";			
		_createGears();
	}


	class OutputSwitch : public LG::SwitchGliph
	{
	public:
		OutputSwitch(int y, NEArgumentBase& new_arg) : LG::SwitchGliph(0, 45, y, 7, LIGHTCYAN, CYAN), arg(new_arg) 
		{
			nobe.back = DARKGRAY;
			nobe.fore = WHITE;
			setValue( ! arg.isEnable());
		}
		virtual NEObject& clone() const 
		{
			return *(new OutputSwitch(*this));
		}
		virtual void onUpdateData()
		{
			LG::SwitchGliph::onUpdateData();
			if(getValue())	//	True면 실제 arg는 false.
			{
				nobe.text = "O";
				text = "-OFF---";
			}
			else
			{
				nobe.text = "<";				
				text = "--WRITE";			
			}
		}
		virtual void onKeyPressed(char inputed)
		{
			SwitchGliph::onKeyPressed(inputed);

			if( ! getValue())
				arg.setEnable(true);
			else
				arg.setEnable(false);
		}
		NEArgumentBase& arg;
	};

	class InputSwitch : public LG::SwitchGliph
	{
	public:
		InputSwitch(int y, NEArgumentBase& new_arg) : LG::SwitchGliph(0, 53, y, 7, LIGHTCYAN, CYAN), arg(new_arg) 
		{		
			nobe.back = DARKGRAY;
			nobe.fore = WHITE;
			setValue(arg.isEnable());
		}
		virtual NEObject& clone() const 
		{
			return *(new InputSwitch(*this));
		}
		virtual void onUpdateData()
		{
			SwitchGliph::onUpdateData();
			if(getValue())
			{
				text = "-READ--";
				nobe.text = ">";
			}
			else
			{
				text = "-OFF---";
				nobe.text = "O";
			}
		}	
		virtual void onKeyPressed(char inputed)
		{
			SwitchGliph::onKeyPressed(inputed);

			if(getValue())
				arg.setEnable(true);
			else
				arg.setEnable(false);
		}
		NEArgumentBase& arg;
	};

	class InputOutputGear : public LG::GearGliph
	{
	public:
		InputOutputGear(int y, NEArgumentBase& new_arg) 
			: LG::GearGliph(0, 45, y, 15, LIGHTCYAN, CYAN), arg(new_arg) 
		{		
			nobe.back = DARKGRAY;
			nobe.fore = WHITE;

			switch(arg.getPurpose())
			{
			case NEArgumentBase::READ_BY:	setValue(-1);	break;
			case NEArgumentBase::WRITTEN:	setValue(1);	break;
			default:								setValue(0);	break;
			}				
		}
		virtual NEObject& clone() const 
		{
			return *(new InputOutputGear(*this));
		}
		virtual void onUpdateData()
		{
			LG::GearGliph::onUpdateData();
			switch(getValue())
			{
			case -1:
				arg.setPurpose(NEArgumentBase::READ_BY);
				text = "<<-----READ------";
				break;

			case 0:
				text = "--------FF---------";
				break;  

			case 1:
				arg.setPurpose(NEArgumentBase::WRITTEN);
				text = "-----WRITE--->>";
				break;
			}
		}
		virtual void onKeyPressed(char inputed)
		{
			GearGliph::onKeyPressed(inputed);

			switch(getValue())
			{
			case -1:
				arg.setEnable(true);
				arg.setPurpose(NEArgumentBase::READ_BY);
				break;

			case 0:
				arg.setEnable(false);
				arg.setPurpose(NEArgumentBase::UNDEFINED);
				break;  

			case 1:
				arg.setEnable(true);
				arg.setPurpose(NEArgumentBase::WRITTEN);
				break;
			}			
		}
		NEArgumentBase& arg;
	};

	class EnableSwitch2 : public LG::SwitchGliph
	{
	public:
		EnableSwitch2(int y, NEArgumentBase& new_arg) 
			: LG::SwitchGliph(0, 45, y, 15, LIGHTCYAN, CYAN), arg(new_arg) 
		{
			setValue(arg.isEnable());
			nobe.back = DARKGRAY;
			nobe.fore = WHITE;
		}
		FUNC_CLONE(EnableSwitch2)

			virtual void onUpdateData()
		{
			LG::SwitchGliph::onUpdateData();

			text = arg.isEnable() ? "------ON!------" : "------OFF------";
		}

		virtual void onKeyPressed(char inputed)
		{
			LG::SwitchGliph::onKeyPressed(inputed);
			switch (inputed)
			{
			case LEFT:
			case RIGHT:
				arg.setEnable(getValue());
				break;
			}

			text = getValue() ? "------ON!------" : "------OFF------";
		}
		NEArgumentBase& arg;
	};

	void _createGears()
	{
		NEArgumentSet& args = castObject().getArguments();
		gears.arr.create(args.getLength());

		for(int n=0; n < args.getLength() ;n++)
		{
			NEArgumentBase& arg = args[n];
			switch(arg.getPurposeLimitation())
			{
			case NEArgumentBase::READ_BY:
				gears.arr.push(InputSwitch(7+n, arg));
				break;

			case NEArgumentBase::WRITTEN:
				gears.arr.push(OutputSwitch(7+n, arg));
				break;

			case NEArgumentBase::READ_OR_WRITTEN:
				gears.arr.push(InputOutputGear(7+n, arg));
				break;

			case NEArgumentBase::NOT_CONCERNED:
			case NEArgumentBase::UNDEFINED:
				gears.arr.push(EnableSwitch2(7+n, arg));

			}
		}
	}

	void _rearrangeGears()
	{
		int h = argument_namelist.height,
			half_h = h / 2,
			head_n = argument_namelist.choosed - half_h;
		if (head_n < 0)
			head_n = 0;
		int	tail_n = head_n + h - 1;		
		if(tail_n > argument_namelist.items.getLengthLastIndex())
		{
			tail_n = argument_namelist.items.getLengthLastIndex();
			head_n = (tail_n - h + 1) > 0 ? (tail_n - h + 1) : 0;
		}


		for(int n = 0; n < gears.arr.getLength(); n++)
		{
			if(	n >= head_n		&&
				n <= tail_n		)
				gears.arr[n].y = 7 + (n - head_n);
			else
				gears.arr[n].y = 85;	//	OUT OF FRAME
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
				enable.Gliph::fore = CYAN;
				enable.Gliph::back = LIGHTCYAN;
			}
			else if (argument_typelist.choosed == 0)
			{
				argument_typelist.choosed = -1;
				argument_namelist.choosed = -1;
				namecode.back = LIGHTCYAN;
				namecode.fore = CYAN;
			}
			else if(enable.Gliph::back == LIGHTCYAN)
			{
				enable.Gliph::back = CYAN;
				enable.fore = LIGHTCYAN;
			}
			break;

		case DOWN:
			if (enable.Gliph::back == LIGHTCYAN)
			{
				enable.Gliph::back = CYAN;
				enable.fore = LIGHTCYAN;
				namecode.back = LIGHTCYAN;
				namecode.fore = CYAN;
			}
			else if(namecode.back == LIGHTCYAN)
			{
				namecode.back = WHITE;
				namecode.fore = BLACK;			
			}
			break;				
		}

		if (enable.Gliph::back == LIGHTCYAN)
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

		switch(inputed)
		{
		case UP:
		case DOWN:	
			{
				for(int n=0; n < gears.arr.getLength() ;n++)
				{
					gears.arr[n].back = CYAN;
					gears.arr[n].fore = LIGHTCYAN;
				}

				Gliph& g = gears.arr[argument_typelist.choosed];
				if( &g)
				{		
					g.back = LIGHTCYAN;
					g.fore = CYAN;				
				}
			}
			_rearrangeGears();
			break;
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
		EnableSwitch() : LG::SwitchGliph(0, 60, 4, 15, CYAN, DARKGRAY) 
		{				
		}
		FUNC_CLONE(EnableSwitch)
			FUNC_TO_OWNER(ModuleTerminal)

			virtual void onUpdateData()
		{
			LG::SwitchGliph::onUpdateData();
			nobe.back = DARKGRAY;
			nobe.fore = WHITE;
		}

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

			text = getValue() ? "------ON!------" : "------OFF-------";				
		}
	};

	class NameGliph : public LG::Gliph
	{
	public:
		NameGliph() : LG::Gliph(0, 60, 5, 15, 1, CYAN, LIGHTCYAN, "") {}
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
		namecode_header;
	NameGliph namecode;
	FloatingPanel argument_panel;
	ModulePanel module_panel;
	ContentPanel content_panel;
	ArgumentHeader argument_header;
	ArgumentNameList argument_namelist;
	ArgumentTypeList argument_typelist;	
	GliphSet gears;
};