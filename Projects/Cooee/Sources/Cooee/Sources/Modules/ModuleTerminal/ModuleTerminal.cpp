#include "ModuleTerminal.hpp"
#include "../Core/Core.hpp"
#include "../MainPopUpMenu/MainPopUpMenu.hpp"
#include "Windows.h"
#pragma comment(lib, "winmm.lib")

class ArgumentPopUp : public LG::ListWindow
{
public:
	ArgumentPopUp() : LG::ListWindow("이 Argument의...", 30, 10, 20, 7, BLACK, WHITE, WHITE, LIGHTCYAN) {}
	FUNC_TO_CALLER(ModuleTerminal)
		virtual NEObject& clone() const {
			return *(new ArgumentPopUp(*this));
	}

	virtual void onUpdateData()
	{
		ListWindow::onUpdateData();

		type_index size = isSelectorArgument() ? 4 : 3;

		list.items.create(size);
		list.items.push("기본 값을 수정한다.");
		list.items.push("넣을 키를 정한다.");
		list.items.push("키를 넣지 않는다.");
		if (size >= 4)
			if (isWantingToLock())
				list.items.push("BindingLock을 헤제한다.");
			else
				list.items.push("BindingLock을 건다.");
	}

	bool isSelectorArgument()
	{
		NEModule& m = toCaller().castObject();
		NEArgumentBase& arg = m.getArguments()[toCaller().argument_namelist.choosed];
		NETArgument<NENodeSelector>* nsarg = cast<NENodeSelector>(arg);
		NETArgument<NEModuleSelector>* msarg = cast<NEModuleSelector>(arg);
		NETArgument<NEKeySelector>* ksarg = cast<NEKeySelector>(arg);

		return(nsarg || msarg || ksarg);
	}
	bool isWantingToLock()
	{
		NEModule& m = toCaller().castObject();
		NEArgumentBase& arg = m.getArguments()[toCaller().argument_namelist.choosed];
		NETArgument<NENodeSelector>* nsarg = cast<NENodeSelector>(arg);
		NETArgument<NEModuleSelector>* msarg = cast<NEModuleSelector>(arg);
		NETArgument<NEKeySelector>* ksarg = cast<NEKeySelector>(arg);

		if(nsarg)
			return nsarg->isWantingToLock();
		if(msarg)
			return msarg->isWantingToLock();
		if(ksarg)
			return ksarg->isWantingToLock();

		return false;
	}
	void switchWantingToLock()
	{
		NEModule& m = toCaller().castObject();
		NEArgumentBase& arg = m.getArguments()[toCaller().argument_namelist.choosed];
		NETArgument<NENodeSelector>* nsarg = cast<NENodeSelector>(arg);
		NETArgument<NEModuleSelector>* msarg = cast<NEModuleSelector>(arg);
		NETArgument<NEKeySelector>* ksarg = cast<NEKeySelector>(arg);

		if(nsarg)
			nsarg->setWantingToLock(!nsarg->isWantingToLock());
		else if(msarg)
			msarg->setWantingToLock(!msarg->isWantingToLock());
		else if(ksarg)
			ksarg->setWantingToLock(!ksarg->isWantingToLock());
	}

	template <typename T>
	NETArgument<T>* cast(NEArgumentBase& arg)
	{
		return dynamic_cast<NETArgument<T>*>(&arg);
	}
	virtual void onItemChoosed(type_index index, const NEString& chosen_content)
	{
		class CodeInputer : public LG::TextListWindow
		{
		public:
			FUNC_TO_CALLER(ArgumentPopUp)
				virtual NEObject& clone() const { return *(new CodeInputer(*this)); }

			CodeInputer(NENode& new_owner)
				: LG::TextListWindow("새로 추가할 키를 선택하세요.",
				25, 7, 30, 10, BLACK,LIGHTGREEN,LIGHTGREEN, BLACK),
				owner(new_owner)
			{
				list.use_matching = true;
			}

			virtual void onFocused()
			{
				if (!&owner) return;
				const NEKeyCodeSet& ks = owner.getKeySet();

				NEModule& m = toCaller().toCaller().castObject();
				NEArgumentBase& arg = m.getArguments()[toCaller().toCaller().argument_namelist.choosed];
				list.text.text = arg.getKeyName();

				list.items.create(ks.getLength());				
				for (int n = 0; n < ks.getLength(); n++)
					if(list.items.find(ks[n].getName()) == NE_INDEX_ERROR)
						list.items.push(ks[n].getName() + "(" + ks[n].getTypeName() + ")");				
			}

			virtual void onInputed(const NEString& inputed)
			{
				NEModule& m = toCaller().toCaller().castObject();
				NEArgumentBase& arg = m.getArguments()[toCaller().toCaller().argument_namelist.choosed];
				if (!&arg)
				{
					::Core::pushMessage("Argument를 찾지 못했습니다.");
					return;
				}

				NEStringSet splited;
				inputed.split("(", splited);
				if(splited.getLength() > 0)
					splited.pop();
				NEString keyname;
				for (int n = 0; n < splited.getLength(); n++)
					keyname += splited[n];

				if(keyname.getLength() <= 0)
					keyname = inputed;

				arg.setKeyName(keyname);

				toCaller().delete_me = delete_me = true;
			}

			NENode& owner;
		};

		NEModule& m = toCaller().castObject();
		NEArgumentSet& args = m.getArguments();

		NEArgumentBase& arg = args[toCaller().argument_namelist.choosed];
		if (!&arg)
		{
			::Core::pushMessage("에러: 선택한 Argument의 인덱스가 ITArgument의 인덱스를 넘었습니다.");
			return;
		}

		switch (index)
		{
		case 0:
			{
				NEEventHandler& handler = Editor::getInstance().getEventHandler();
				NEKey& dk = arg.getDefaultKey();

				if (dk.isSubClassOf(NEType::NEMODULE_CODESET_KEY) ||
					dk.isSubClassOf(NEType::NENODE_CODESET_KEY))
					::Core::openModifierFrom(toCaller().getPath() + "/" + toCaller().argument_namelist.choosed);
				else
					::Core::openModifierFrom(arg.getDefaultKey(), true);

				delete_me = true;
			}
			break;

		case 1:
			{
				ModuleTerminal& mt = toCaller();
				call(CodeInputer(mt.getOwnerNodeOf(mt.castObject())));
			}
			break;

		case 2:
			arg.setKeyName(NETString());
			delete_me = true;
			break;

		case 3:
			if (!isSelectorArgument()) return;
			switchWantingToLock();
			break;
		}
	}
};


void ModuleTerminal::ArgumentNameList::onKeyPressed(int inputed)
{


	ListGliph::onKeyPressed(inputed);

	switch(inputed)
	{
	case CONFIRM:
		toOwner()->call(ArgumentPopUp());
		break;

	case CANCEL:	
		LG::Core::open(MainPopUpMenu(*toOwner()));
		break;

	case CLOSE:
		toOwner()->delete_me = true;
		break;
	}		
}

NENode& ModuleTerminal::getOwnerNodeOf(NEModule& target)
{
	class MyHandler : public Core::onObjectFound
	{
	public:
		MyHandler() : last_pointer(0) {}
		virtual void onNodeFound(NENode& node)
		{
			last_pointer = &node;
		}
		NENode* last_pointer;
	};

	MyHandler myhandler;
	Core::getObjectBy(getPath(), myhandler);

	return *myhandler.last_pointer;
}

void ModuleTerminal::ModulePanel::onUpdateData()
{
	if( ! &toOwner()->castObject())
	{
		toOwner()->delete_me = true;

		::Core::pushMessage("잘못된 경로로 참조했습니다.");				
	}
	const NEExportable::ModuleHeader& header = toOwner()->castObject().getHeader();
	text =	"\t"	+ header.getName() + " #" + header.getRevision() + "\n" +
		"\tby " + header.getDeveloper() + "\ton " + header.getReleaseDate();
}

ModuleTerminal::FloatingPanel::FloatingPanel()
: LG::FloatingGliph(0, 0, 60, 7, DARKGRAY, WHITE)
{
	term_for_hiding -= 4500;
}