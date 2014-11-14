#include "Command.hpp"
#include "../Core/Core.hpp"
#include "../Planetarium/Planetarium.hpp"
#include "../HeaderModifier/HeaderModifier.hpp"
#include "../CommandListWindow/CommandListWindow.hpp"
#include "../ModuleEncyclo/ModuleEncyclo.hpp"
#include "../NodeSetTerminal/NodeSetTerminal.hpp"
#include "../GuideEncyclo/GuideEncyclo.hpp"
#include "../Really/Really.hpp"

//		N:1 삽입(지정) 용 함수 템플릿
template <typename KeyContainer, typename Source>
bool _pasteInKeyContainer(NEObject& cont, const NEObject& src, NEType::Type src_type, type_index index = -1)
{
	NEType::Type cont_type = KeyContainer().getType();

	if( ! &cont							||
		! &src							||
		! cont.isSubClassOf(cont_type)	||
		! src.isSubClassOf(src_type)	)
		return false;

	KeyContainer& c = static_cast<KeyContainer&>(cont);
	const Source& s = static_cast<const Source&>(src);

	if(c.getLength() == c.getSize())
		c.resize(c.getLength() + 1);

	if(index != -1)
		c.insert(index, s);
	else
		c.push(s);

	return true;
}

//	Helper 함수 템플릿:
template <typename Target, typename Source>
bool _pasteTryEverything(NEObject& target, NEObject& parent, const NEObject& source, NEType::Type src_type, type_index index)
{
	if(_pasteInKeyContainer<Target, Source>(parent, source, src_type, index))
		return true;

	return _pasteInKeyContainer<Target, Source>(target, source, src_type);
}

Command::Command(const NEString& names_delimetered_with_space, const NEString& new_help)
: help(new_help)
{
	names_delimetered_with_space.split(" ", names);
}

type_result Command::isValid() const {return 0;}
NEBinaryFileSaver& Command::serialize(NEBinaryFileSaver& saver) const { return saver; }
NEBinaryFileLoader& Command::serialize(NEBinaryFileLoader& loader) { return loader; }
void Command::release() {}
bool Command::operator!=(const Command& rhs) const { return names == rhs.names && help == rhs.help; }

ListCommand::ListCommand() 
: Command("list ls", 
		  "해당 경로의 내용을 화면에 출력합니다.\n"
		  "별칭	: list, ls\n"
		  "사용법 : list <경로>") 
{
}

void printShortCutSet(const NEShortCutSet& shorts)
{
	for(int n=0; n < shorts.getLength() ;n++)
	{
		cout << n << ": ";
		for(int x=0; x < shorts[n].getLength() ;x++)
			cout << shorts[n][x] << ", ";
		cout << "\n";
	}
}

NE::NEString ListCommand::execute(const NEStringSet& parameters) 
{
	if(parameters.getLength() <= 0)
		return "ERROR: 인자가 필요합니다.";

	if(parameters[0] == "-cache")    //    shortcutset을 출력한다.
	{
		system("cls");
		const NEEnlistableManager* mng = 0;
		if( ! ::Core::isObservingDebug())
		{
			mng = &Editor::getInstance().getScriptEditor();
			cout << "ScriptEditor:\n";
		}
		else
		{
			mng = &Kernal::getInstance().getNodeManager();
			cout << "NodeManager:\n";
		}

		cout << "Script  -------------------------\n";    
		printShortCutSet(mng->getScriptShortCutSet());
		cout << "Name    -------------------------\n";    
		printShortCutSet(mng->getNameShortCutSet());
		cout << "Group   -------------------------\n";
		printShortCutSet(mng->getGroupShortCutSet());
		cout << "Priority-------------------------\n";    
		printShortCutSet(mng->getPriorityShortCutSet());

		system("pause");
		LG::Core::back_buffer.readyBufferToDraw();
	}
	else
	{
		const NEString& path = parameters[0];
		NEObject& parsed = ::Core::getObjectBy(path);
		if( ! &parsed)
			return "ERROR: " + path + "가 잘못된 경로 입니다.";

		if(parsed.isSubClassOf(NEType::NEKEY))
			::Core::openModifierFrom((NEKey&)parsed);
		else
			::Core::openModifierFrom(path);
	}

	return "";
}

NE::NEString CloseCommand::execute(const NEStringSet& parameters)
{
	LG::WindowList& wins = LG::Core::getWindowList();
	if(wins.getLength() > 1)
		wins[0].delete_me = true;
	else if( ! ::Core::isObservingDebug())
		::Core::commander.command("exit");
	else
		::Core::pushMessage("이 창은 닫을 수 없어요");

	return "";
}

NE::NEString VersionCommand::execute(const NEStringSet& parameters)
{
	LG::Core::getWindowList().pushFront(LG::MessageWindow(NEString(_VERSION_STRING) + "\n\tby " + _DEVELOPER + "\n\ton " + _DATE, WHITE, LIGHTRED));
	return "";
}

NE::NEString PlanetarizeCommand::execute(const NEStringSet& parameters)
{
	LG::Core::open(Planetarium());

	if(parameters.getLength() > 0)
	{
		NEObject& parsed = ::Core::getObjectBy(parameters[0]);
		if( ! &parsed) return "ERROR: 주어진 경로가 잘못되었네요.\n주어진 경로 : " + parameters[0];
		Planetarium& planetarium = dynamic_cast<Planetarium&>(LG::Core::getWindowList()[0]);
		planetarium.setFocus(parsed);
	}

	return "";
}

NE::NEString CopyCommand::execute(const NEStringSet& parameters)
{
	if(::Core::isObservingDebug())
		return "ERROR: 테스트 영역에서는 수정과 열람만 가능합니다.";

	type_result result = RESULT_SUCCESS;
	switch(parameters.getLength())
	{
	case 1:
		::Core::setPathToBeCopied(parameters[0]);
		return "";

	case 2:
		::Core::setPathToBeCopied(parameters[0]);
		return ::Core::commander.command("paste " + parameters[1]);

	default:
		return "ERROR: 경로를 입력하세요";
	}	
}

NE::NEString CutCommand::execute(const NEStringSet& parameters)
{
	if(::Core::isObservingDebug())
		return "ERROR: 테스트 영역에서는 수정과 열람만 가능합니다.";

	type_result result = RESULT_SUCCESS;
	switch(parameters.getLength())
	{
	case 1:
		::Core::setPathToBeCutOff(parameters[0]);
		return "";

	case 2:
		::Core::setPathToBeCutOff(parameters[0]);
		return ::Core::commander.command("paste " + parameters[1]);

	default:
		return "ERROR: 경로를 입력하세요";
	}	
}

NEType::Type AddCommand::_findKeyTypeBy(const NEString& type_name)
{
	const NEKeySet& ks = Kernal::getInstance().getKeyManager().getKeySet();
	for(int n=0; n < ks.getLength() ;n++)
		if(type_name == ks[n].getTypeName())
			return ks[n].getType();

	return NEType::UNDEFINED;
}

NE::NEString AddCommand::execute(const NEStringSet& parameters)
{
	if(::Core::isObservingDebug())
		return "ERROR: 테스트 영역에서는 수정과 열람만 가능합니다.";
	if(parameters.getLength() <= 0)    return "ERROR: Container의 경로를 입력하세요";

	NENodeCodeSet* nsc = 0;
	NEModuleCodeSet* msc = 0;        
	type_index index_to_add = NE_INDEX_ERROR;
	NEObject* parent = 0x00;

	if(parameters[0] == "-node")
	{
		if(parameters.getLength() < 2) return NEString("ERROR: 인자의 갯수가 2개여야 합니다. \n현재 인자 수 : ") + parameters.getLength();
		_searchParent(parameters[1], index_to_add, &parent);
		NEObject& target = ::Core::getObjectBy(parameters[1]);

		NENode source;
		if( ! _pasteTryEverything<NENodeCodeSet, NENode>(target, *parent, source, NEType::NENODE, index_to_add))
			return    NEString("ERROR: 주어진 타겟(") + target.getTypeName() + ")과 원본(" + 
			source.getTypeName() + ") 간에는 Paste가 불가능 합니다.";
	} 
	else if(parameters[0] == "-module")
	{
		if(parameters.getLength() < 5) return NEString("ERROR: 인자의 갯수가 5개여야 합니다. \n현재 인자 수 : ") + parameters.getLength();
		_searchParent(parameters[4], index_to_add, &parent);
		NEObject& target = ::Core::getObjectBy(parameters[4]);

		NEExportable::Identifier identifier(parameters[1], parameters[2], parameters[3].toInt());
		const NEModule& source = Kernal::getInstance().getModuleManager().getModule(identifier);
		if( ! &source) return "ERROR: 잘못된 Identifier 입니다.";

		if( ! _pasteTryEverything<NEModuleCodeSet, NEModule>(target, *parent, source, NEType::NEMODULE, index_to_add))
			return    NEString("ERROR: 주어진 타겟(") + target.getTypeName() + ")과 원본(" + 
			source.getTypeName() + ") 간에는 Paste가 불가능 합니다.";
	}
	else if(parameters[0] == "-key")
	{
		if(parameters.getLength() < 3) return NEString("ERROR: 인자의 갯수가 3개여야 합니다. \n현재 인자 수 : ") + parameters.getLength();

		const NEKey& source = Kernal::getInstance().getKeyManager().getKey(_findKeyTypeBy(parameters[1]));
		if( ! &source) return "ERROR: " + parameters[1] + "에 해당하는 키가 없습니다.";
		_searchParent(parameters[2], index_to_add, &parent);
		NEObject& target = ::Core::getObjectBy(parameters[2]);

		if( ! _pasteTryEverything<NEKeyCodeSet, NEKey>(target, *parent, source, NEType::NEKEY, index_to_add))
			return    NEString("ERROR: 주어진 타겟(") + target.getTypeName() + ")과 원본(" + 
			source.getTypeName() + ") 간에는 Paste가 불가능 합니다.";
	}

	return "";
}

NE::NEString DeleteCommand::execute(const NEStringSet& parameters)
{
	if(::Core::isObservingDebug())
		return "ERROR: 테스트 영역에서는 수정과 열람만 가능합니다.";
	if(parameters.getLength() <= 0)	return "ERROR: 경로를 입력하세요.";

	type_index idx_to_del = 0;
	NEObject* parent = 0x00;
	_searchParent(parameters[0], idx_to_del, &parent);

	NENodeCodeSet* ncs = 0x00;
	NEModuleCodeSet* mcs = 0x00;
	type_result result = RESULT_SUCCESS;

	::Core::setPathToBeCopied("");
	//	왜 복사용 Path를 지우는 가:
	//		이미 지워진 경로를 참조 할 수 있기 때문이다.
	//		제대로 하려면 Delete해서 복사용 Path 자신이나 조상들 중 
	//		하나를 삭제한다면, Path를 null로 만들어야 하나
	//		조상을 알아내는 방법이 현재는 없으므로 귀찮음.

	if(parent->isSubClassOf(NEType::NENODE_CODESET_KEY))
		ncs = &((NENodeCodeSetKey*) parent)->getValue();
	if(parent->isSubClassOf(NEType::NENODE_CODESET))
	{
		if( ! ncs)
			ncs = (NENodeCodeSet*) parent;
		if(idx_to_del > ncs->getLengthLastIndex())
			return "ERROR: 인덱스가 실제보다 더 큽니다.";
		ncs->remove(idx_to_del);
		return "";
	}

	if(parent->isSubClassOf(NEType::NEMODULE_CODESET_KEY))
		mcs = &((NEModuleCodeSetKey*) parent)->getValue();

	if(parent->isSubClassOf(NEType::NEMODULE_CODESET))
	{
		if( ! mcs)
			mcs = (NEModuleCodeSet*) parent;
		if(idx_to_del > mcs->getLengthLastIndex())
			return "ERROR: 인덱스가 실제보다 더 큽니다.";
		mcs->remove(idx_to_del);
		return "";
	}

	if(parent->isSubClassOf(NEType::NEKEY_CODESET))
	{
		NEKeyCodeSet& kcs = (NEKeyCodeSet&) *parent;
		if(idx_to_del > kcs.getLengthLastIndex())
			return "ERROR: 인덱스가 실제보다 더 큽니다.";
		kcs.remove(idx_to_del);
		return "";
	}

	return (NEResult::hasError(result)) ? "ERROR: 삽입 도중 에러가 발생했습니다." : "";
}

NE::NEString OrphanCommand::_searchParent(const NEString& full_path, type_index& index_to_insert, NEObject** parent_to_insert)
{
	NEStringSet splited;
	full_path.split("/", splited);
	if(splited.getLength() <= 0)
		return "ERROR: 주어진 경로가 \"/\" 여서는 안됍니다.";
	NEString parent_path = "/";
	index_to_insert = splited[splited.getLengthLastIndex()].toInt();
	for(int n=0; n < splited.getLength()-1 ;n++)
		parent_path += splited[n] + "/";

	*parent_to_insert = &::Core::getObjectBy(parent_path);
	if( ! *parent_to_insert) return "ERROR: 해당 경로(" + parent_path + ")가 잘못됐네요.";

	return "";
}

//	Paste:
//		Paste의 동작:
//			Paste의 사전 공통 부분:
//				타겟 경로(= parameters[0]) 가 원본 경로(= ::Core::path_to_be_copied)
//				의 타입을 각각 얻어낸다. 이하 타겟타입, 원본 타입이라 한다.
//				다음은, Paste 동작의 종류와 그쪽으로 분기하는 조건을 서술한다.
//
//			N:1 삽입 연산:	타겟객체 안에 원본객체를 하나 삽입한다. (push)
//							타겟 타입이 원본타입의 Container 일 경우.
//							Container 여부는 직접 if 문으로 확인 할 수 밖에 없다. 
//							(프레임워크의 RTTI가 빈약하다)
//
//			N:1 지정 삽입:	미리 어느 index로 넣고 싶다는 인덱스도 제공을 한 상태이다.
//							N:1과 동일하되, push 가 아니라 insert로 연산한다.
//
//		Paste 알고리즘:
//			타입 검사하고 캐스팅을 하는 부분은 함수 템플릿으로 대체한다.
//			각 함수 템플릿은 연산이 성공 할 시 true를 반환한다.
//			Paste 함수에서는 반환값이 true가 나올때까지 가능한 한 모든 조합의 
//			함수템플릿을 호출한다.
//			
NE::NEString PasteCommand::execute(const NEStringSet& parameters)
{
	if(::Core::isObservingDebug())
		return "ERROR: 테스트 영역에서는 수정과 열람만 가능합니다.";
	if(parameters.getLength() <= 0) return "ERROR: 경로를 입력하세요";
	if(	::Core::path_to_be_copied.getLength() <= 1) return "ERROR: 복사할 원본을 정해주세요";

	NENodeCodeSet* ncs = 0;
	NEModuleCodeSet* mcs = 0;
	type_result result = RESULT_SUCCESS;

	NEObject* parent = 0;
	type_index index;
	_searchParent(parameters[0], index, &parent);

	NEObject& source = ::Core::getObjectBy(::Core::path_to_be_copied);
	NEObject& target = ::Core::getObjectBy(parameters[0]);


	//	main:
	if( ! _pasteTryEverything<NENodeCodeSet, NENode>(target, *parent, source, NEType::NENODE, index))
		if( ! _pasteTryEverything<NEModuleCodeSet, NEModule>(target, *parent, source, NEType::NEMODULE, index))
			if( ! _pasteTryEverything<NEKeyCodeSet, NEKey>(target, *parent, source, NEType::NEKEY, index))
				return NEString("ERROR: 주어진 타겟(") + target.getTypeName() + ")과 원본(" + 
				source.getTypeName() + ") 간에는 Paste가 불가능 합니다.";


	//	post:
	if(::Core::is_cutting_off)
	{
		::Core::commander.command("delete " + ::Core::path_to_be_copied);
		::Core::setPathToBeCopied("");
	}
	return (NEResult::hasError(result)) ? "ERROR: 삽입 도중 에러가 발생했습니다." : "";
}

NE::NEString RunCommand::execute(const NEStringSet& parameters)
{
	NEEventHandler& handler = Editor::getInstance().getEventHandler();

	if(parameters.getLength() <= 0)
	{
		if(handler.isTestRunning())
		{
			handler.resumeTest();
			::Core::test_running_count = -1;
		}
		else
		{
			handler.initiateTest();
			_initiateDebug();
			::Core::test_running_count = -1;
		}
	}
	else
	{
		if(parameters[0] == "-new")
		{
			handler.initiateTest();
			_initiateDebug();
			::Core::test_running_count = parameters.getLength() > 1 ? parameters[1].toInt() : -1;
		}
		else if(parameters[0] == "-stop")
		{
			handler.stopTest();
			::Core::commander.command("observe -script");
			::Core::test_running_count = 0;
		}
		else
		{
			::Core::test_running_count = parameters[0].toInt();
			if(handler.isTestRunning())
				handler.resumeTest();
			else
			{
				handler.initiateTest();
				_initiateDebug();
			}
		}
	}

	return "";
}
void RunCommand::_initiateDebug()
{
	::Core::initializeWindows(::Core::script_windows);
	::Core::initializeWindows(::Core::debug_windows);
	::Core::commander.command("observe -debug -force");
}

NE::NEString SaveCommand::execute(const NEStringSet& parameters)
{
	NEString filename = (parameters.getLength() <= 0) ?
		Kernal::getInstance().getScriptManager().getScriptFilePath()
		:
	parameters[0];

	NEEventHandler& handler = Editor::getInstance().getEventHandler();
	if(NEResult::hasError(handler.saveScriptFile(NETString(filename))))
		return NEString("ERROR: ") + filename + "으로 파일 저장 실패.";

	return "";
}
NE::NEString LoadCommand::execute(const NEStringSet& parameters)
{
	if(parameters.getLength() <= 0) return "ERROR: 읽어들일 파일명을 입력해주세요.";

	class Really : public LG::QueryWindow
	{
	public:
		Really(const NEString& path) 
			: LG::QueryWindow("저장되지 않는 내용은 사라지는데, 괜찮겠어요?", LIGHTRED, RED, true),
			_filepath(path) {}
		virtual NEObject& clone() const { return *(new Really(*this)); }
		virtual void onButtonPressed(bool witch_button)
		{
			if(witch_button)
			{
				NEEventHandler& handler = Editor::getInstance().getEventHandler();
				if(NEResult::hasError(handler.loadScriptFile(NETString(_filepath))))
					::Core::pushMessage("ERROR: 파일 로드 실패.");
				else
				{
					::Core::initializeWindows(::Core::debug_windows);
					::Core::initializeWindows(::Core::script_windows);
					::Core::commander.command("observe -script -force");
				}
			}

			delete_me = true;
		}

		NEString _filepath;
	};

	LG::Core::open(Really(parameters[0]));

	return "";
}
NE::NEString NewCommand::execute(const NEStringSet& parameters)
{
	class Really : public LG::QueryWindow
	{
	public:
		Really() : LG::QueryWindow("저장되지 않는 내용은 사라지는데, 괜찮겠어요?", LIGHTRED, RED, true) {}
		virtual NEObject& clone() const { return *(new Really(*this)); }
		virtual void onButtonPressed(bool witch_button)
		{
			if(witch_button)
			{
				NEEventHandler& handler = Editor::getInstance().getEventHandler();
				if(NEResult::hasError(handler.initializeNewFile()))
				{
					::Core::pushMessage("ERROR: 새로운 파일 시작 실패.");
					return;
				}

				::Core::initializeWindows(::Core::debug_windows);
				::Core::initializeWindows(::Core::script_windows);
				::Core::commander.command("observe -script -force");
			}

			delete_me = true;
		}
	};

	LG::Core::open(Really());

	return "";
}
NE::NEString HelpCommand::execute(const NEStringSet& parameters)
{
	switch(parameters.getLength())
	{
	case 0:
		LG::Core::open(GuideEncyclo());
		break;

	case 1:
		if(parameters[0] == "-module")
			LG::Core::open(ModuleEncyclo());	
		else if(parameters[0] == "-command")
			LG::Core::open(CommandListWindow());
		break;

	case 2:		
		if(parameters[0] == "-module")
		{
			NEObject& obj = ::Core::getObjectBy(parameters[1]);
			if( ! obj.isSubClassOf(NEType::NEMODULE))
				return NEString("ERROR: 주어진 경로(") + parameters[1] + ")는 모듈이 아닙니다.";

			LG::Core::open(ModuleEncyclo(static_cast<NEModule*>(&obj)));
		}
		break;

	default:
		return "ERROR: 명령이 잘못되었습니다.";
	}

	return "";
}
NE::NEString HeaderCommand::execute(const NEStringSet& parameters)
{
	LG::Core::open(HeaderModifier());
	return "";
}
NE::NEString ObserveCommand::execute(const NEStringSet& parameters)
{
	if(parameters.getLength() <= 0)
	{
		if(::Core::isObservingDebug())
			_switchTo(::Core::script_windows);
		else
			_switchTo(::Core::debug_windows);
	}
	else
	{
		bool is_forcing = parameters.getLength() >= 2 ? parameters[1] == "-force" : false;
		if(parameters[0] == "-debug")
			_switchTo(::Core::debug_windows, is_forcing);
		else if(parameters[0] == "-script")
			_switchTo(::Core::script_windows, is_forcing);
	}

	return "";
}
void ObserveCommand::_switchTo(LG::WindowList& windows, bool is_forcing)
{
	if( ! is_forcing && windows.getLength() <= 0)
		return;

	LG::Core::setWindowList(windows);
}
NEString ExitCommand::execute(const NEStringSet& parameters)
{
	LG::Core::open(Really());

	return "";
}
