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

		type_index size = isSelectorArgument() ? 3 : 2;

		list.items.create(size);
		list.items.push("넣을 키를 정한다.");
		list.items.push("기본 값을 수정한다.");
		if (size >= 3)
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
				25, 7, 30, 10, BLACK, LIGHTGREEN, LIGHTGREEN, BLACK),
				owner(new_owner), _local_keys_listed(false)
			{
				list.use_matching = true;
			}


			virtual void onFocused()
			{
				NEModule& m = toCaller().toCaller().castObject();
				NEArgumentBase& arg = m.getArguments()[toCaller().toCaller().argument_namelist.choosed];
				list.text.text = arg.getKeyName();			

				list.items = _updateList(true);
				if(	(list.text.text == "" || list.text.text.getLength() <= 0)	&&
					list.items.getLength() > 0									)
					list.text.text = list.items[0];
			}

			bool _findParsedKeyName(const NEStringSet& strs, const NEString& target)
			{
				NEString lowered = target.toLowerCase();
				for(int n = 0; n < strs.getLength(); n++)
				{
					if(_extractKeyName(strs[n]).toLowerCase().isEqualElement(target))
						return true;
				}

				return false;
			}

			virtual void onInputed(const NEString& inputed)
			{
				if( ! &inputed) return;
				NEModule& m = toCaller().toCaller().castObject();
				NEArgumentBase& arg = m.getArguments()[toCaller().toCaller().argument_namelist.choosed];
				//	주어진 입력이 LocalKeySet에 있는지, KeySet에 있는지를 확인하고
				//	양쪽 모두에 없다면, 기본값으로 집어넣고 키이름을 ""로 만든다.
				NEString	keyname = _extractKeyName(inputed),
					lowerd = keyname.toLowerCase();

				if( ! _findParsedKeyName(_updateListFromKeySet(true), lowerd) &&
					! _findParsedKeyName(_updateListFromLocalKeySet(true), lowerd))
				{					
					arg.getDefaultKey() = NEStringKey(inputed);
					arg.setKeyName("");
				}
				else
					arg.setKeyName(keyname);

				toCaller().delete_me = delete_me = true;
			}

			virtual void onKeyPressed(int inputed)
			{
				TextListWindow::onKeyPressed(inputed);

				switch(inputed)
				{
				case UP: case DOWN: case LEFT: case RIGHT: 
					break;

				default:
					list.items = _updateList(false);
				}
			}

			NEStringSet _updateList(bool force)
			{
				if (list.text.text.getLength() > 0	&&
					list.text.text[0] == '$'		)
					return _updateListFromLocalKeySet(force);
				else
					return _updateListFromKeySet(force);
			}

			NEStringSet _updateListFromKeySet(bool force)
			{
				if (!&owner) return list.items;
				if (!force && !_local_keys_listed) return list.items;
				const NEKeyCodeSet& ks = owner.getKeySet();

				NEStringSet to_return;
				to_return.create(ks.getLength());
				for (int n = 0; n < ks.getLength(); n++)
					if (to_return.find(ks[n].getName()) == NE_INDEX_ERROR)
						to_return.push(ks[n].getName() + "(" + ks[n].getTypeName() + ")");

				if( ! force)
					_local_keys_listed = false;
				return to_return;
			}		
			NEString _extractKeyName(const NEString& full_string)
			{
				NEStringSet splited;
				full_string.split("(", splited);
				if (splited.getLength() > 0)
					splited.pop();
				NEString to_return;
				for (int n = 0; n < splited.getLength(); n++)
					to_return += splited[n];

				if (to_return.getLength() <= 0)
					to_return = full_string;

				return to_return;
			}
			NEStringSet _updateListFromLocalKeySet(bool force)
			{
				if (!force && _local_keys_listed) return list.items;
				typedef NENodeManager::LocalStack::PersistentKeySet PersistentKeySet;
				const PersistentKeySet& ks = Kernal::getInstance().getNodeManager().getLocalStack().getLocalKeySet();

				NEStringSet to_return;
				to_return.create(ks.getLength());
				for (int n = 0; n < ks.getLength(); n++)
				{
					const NEKey& k = ks[n];
					if( ! &k) continue;
					if(to_return.find(k.getName()) == NE_INDEX_ERROR)
						to_return.push(k.getName() + "(" + k.getTypeName() + ")");
				}					

				if( ! force)
					_local_keys_listed = true;
				return to_return;
			}

			NENode& owner;
			bool _local_keys_listed;
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
		case 1:
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

		case 0:
			{
				ModuleTerminal& mt = toCaller();
				call(CodeInputer(mt.getOwnerNodeOf(mt.castObject())));
			}
			break;

		case 2:
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