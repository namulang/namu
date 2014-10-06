#include "Command.hpp"
#include "../Core/Core.hpp"
#include "../Planetarium/Planetarium.hpp"
#include "../HeaderModifier/HeaderModifier.hpp"
#include "../CommandListWindow/CommandListWindow.hpp"
#include "../ModuleEncyclo/ModuleEncyclo.hpp"

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

NE::NEString ListCommand::execute(const NEStringSet& parameters) 
{
	const NEString& path = parameters[0];
	NEObject& parsed = ::Core::getObjectBy(path);

	if(parsed.isSubClassOf(NEType::NEKEY))
		::Core::openModifierFrom((NEKey&)parsed);
	else
		::Core::openModifierFrom(path);

	return "";
}

NE::NEString CloseCommand::execute(const NEStringSet& parameters)
{
	LG::WindowList& wins = LG::Core::windows;
	if(wins.getLength() > 0)
		wins[0].delete_me = true;

	return "";
}

NE::NEString VersionCommand::execute(const NEStringSet& parameters)
{
	LG::Core::windows.pushFront(LG::MessageWindow(NEString(_VERSION_STRING) + "\n\tby " + _DEVELOPER + "\n\ton " + _DATE, WHITE, LIGHTRED));
	return "";
}

NE::NEString PlanetarizeCommand::execute(const NEStringSet& parameters)
{
	Planetarium planetarium;

	if(parameters.getLength() > 0)
	{
		NEObject& parsed = ::Core::getObjectBy(parameters[0]);
		if( ! &parsed) return "ERROR: 주어진 경로가 잘못되었네요.\n주어진 경로 : " + parameters[0];
		planetarium.setFocus(parsed);
	}

	LG::Core::open(planetarium);
	return "";
}

NE::NEString CopyCommand::execute(const NEStringSet& parameters)
{
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
	if(parameters.getLength() <= 0)	return "ERROR: Container의 경로를 입력하세요";

	NENodeCodeSet* nsc = 0;
	NEModuleCodeSet* msc = 0;		
	if(parameters[0] == "-node")
	{
		if(parameters.getLength() < 2) return NEString("ERROR: 인자의 갯수가 2개여야 합니다. \n현재 인자 수 : ") + parameters.getLength();
		NEObject& parsed = ::Core::getObjectBy(parameters[1]);
		if( ! &parsed) return "ERROR: 경로가 잘못 됐네요.";
		switch(parsed.getType())
		{
		case NEType::NENODE_CODESET_KEY:
			nsc = &((NENodeCodeSetKey&) parsed).getValue();

		case NEType::NENODE_CODESET:
			if( ! nsc)
				nsc = (NENodeCodeSet*) &parsed;

			if(nsc->getLength() >= nsc->getSize())
				nsc->resize(nsc->getSize() + 1);

			nsc->push(NENode());
			break;

		default:
			return NEString("ERROR: 잘못된 경로입니다. 주어진 타입이 ") + parsed.getTypeName();
		}
	} 
	else if(parameters[0] == "-module")
	{
		if(parameters.getLength() < 5) return NEString("ERROR: 인자의 갯수가 5개여야 합니다. \n현재 인자 수 : ") + parameters.getLength();
		NEObject& parsed = ::Core::getObjectBy(parameters[4]);
		if( ! &parsed) return "ERROR: 경로가 잘못 됐네요.";

		NEExportable::Identifier identifier(parameters[1], parameters[2], parameters[3].toInt());

		switch(parsed.getType())
		{
		case NEType::NEMODULE_CODESET_KEY:
			msc = &((NEModuleCodeSetKey&) parsed).getValue();

		case NEType::NEMODULE_CODESET:
			{
				if( ! msc)
					msc = (NEModuleCodeSet*) &parsed;

				if(msc->getLength() >= msc->getSize())
					msc->resize(nsc->getSize() + 1);

				msc->push(Kernal::getInstance().getModuleManager().getModule(identifier));
			}			
			break;

		default:
			return NEString("ERROR: 잘못된 경로입니다. 주어진 타입이 ") + parsed.getTypeName();
		}
	}
	else if(parameters[0] == "-key")
	{
		if(parameters.getLength() < 3) return NEString("ERROR: 인자의 갯수가 3개여야 합니다. \n현재 인자 수 : ") + parameters.getLength();

		const NEKey& source = Kernal::getInstance().getKeyManager().getKey(_findKeyTypeBy(parameters[1]));
		if( ! &source) return "ERROR: " + parameters[1] + "에 해당하는 키가 없습니다.";
		NEObject& parsed = ::Core::getObjectBy(parameters[2]);
		if( ! &parsed) return "ERROR: 경로가 잘못 됐네요.";

		switch(parsed.getType())
		{
		case NEType::NEKEY_CODESET:
			{
				NEKeyCodeSet& kcs = (NEKeyCodeSet&) parsed;
				if(kcs.getLength() >= kcs.getSize())
					kcs.resize(kcs.getSize() + 1);

				kcs.push(source);
			}

			break;

		default:
			return NEString("ERROR: 잘못된 경로입니다. 주어진 타입이 ") + parsed.getTypeName();
		}
	}

	return "";
}

NE::NEString DeleteCommand::execute(const NEStringSet& parameters)
{
	if(parameters.getLength() <= 0)	return "ERROR: 경로를 입력하세요.";

	type_index idx_to_del = 0;
	NEObject* parent = 0x00;
	_searchParent(parameters[0], idx_to_del, &parent);

	NENodeCodeSet* ncs = 0x00;
	NEModuleCodeSet* mcs = 0x00;
	type_result result = RESULT_SUCCESS;
	switch(parent->getType())
	{
	case NEType::NENODE_CODESET_KEY:
		ncs = &((NENodeCodeSetKey*) parent)->getValue();

	case NEType::NENODE_CODESET:
		if( ! ncs)
			ncs = (NENodeCodeSet*) parent;
		if(idx_to_del > ncs->getLengthLastIndex())
			return "ERROR: 인덱스가 실제보다 더 큽니다.";
		ncs->remove(idx_to_del);
		break;

	case NEType::NEMODULE_CODESET_KEY:
		mcs = &((NEModuleCodeSetKey*) parent)->getValue();

	case NEType::NEMODULE_CODESET:
		if( ! mcs)
			mcs = (NEModuleCodeSet*) parent;
		if(idx_to_del > mcs->getLengthLastIndex())
			return "ERROR: 인덱스가 실제보다 더 큽니다.";
		mcs->remove(idx_to_del);
		break;

	case NEType::NEKEY_CODESET:
		{
			NEKeyCodeSet& kcs = (NEKeyCodeSet&) *parent;
			if(idx_to_del > kcs.getLengthLastIndex())
				return "ERROR: 인덱스가 실제보다 더 큽니다.";
			kcs.remove(idx_to_del);
		}
		break;

	default:
		return "ERROR: 주어진 경로는 삭제가 불가능 합니다.";
	}

	return (NEResult::hasError(result)) ? "ERROR: 삽입 도중 에러가 발생했습니다." : "";
}

NE::NEString OrphanCommand::_searchParent(const NEString& full_path, type_index& index_to_insert, NEObject** parent_to_insert)
{
	NEStringSet splited;
	full_path.split("/\\", splited);
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

NE::NEString PasteCommand::execute(const NEStringSet& parameters)
{
	if(parameters.getLength() <= 0) return "ERROR: 경로를 입력하세요";

	NENodeCodeSet* ncs = 0;
	NEModuleCodeSet* mcs = 0;
	type_result result = RESULT_SUCCESS;
	NEObject* parent = 0;
	type_index index;
	_searchParent(parameters[0], index, &parent);

	NEObject& source = ::Core::getObjectBy(::Core::path_to_be_copied);
	if( ! parent) return "ERROR: 주어진 경로(" + parameters[0] + ")가 잘못되었습니다.";
	switch(parent->getType())
	{
	case NEType::NENODE_CODESET_KEY:
		ncs = &((NENodeCodeSetKey*)parent)->getValue();

	case NEType::NENODE_CODESET:
		if( ! ncs)
			ncs = (NENodeCodeSet*) parent;
		{
			if(source.getType() != NEType::NENODE)			
				return "ERROR: 주어진 경로에 " + NEString(source.getTypeName()) + "을 넣을 수 없습니다.";
			NENode& node = static_cast<NENode&>(source);

			result = ncs->insert(index, node);
		}		
		break;

	case NEType::NEMODULE_CODESET_KEY:
		mcs = &((NEModuleCodeSetKey*)parent)->getValue();

	case NEType::NEMODULE_CODESET:
		if( ! mcs)
			mcs = (NEModuleCodeSet*) parent;
		{
			if(source.getType() != NEType::NEMODULE)
				return "ERROR: 주어진 경로에 " + NEString(source.getTypeName()) + "을 넣을 수 없습니다.";
			NEModule& module = static_cast<NEModule&>(source);

			result = mcs->insert(index, module);
		}
		break;

	case NEType::NEKEY_CODESET:
		{
			NEKeyCodeSet& kcs = (NEKeyCodeSet&) *parent;
			if(source.getType() != NEType::NEKEY)
				return "ERROR: 주어진 경로에 " + NEString(source.getTypeName()) + "을 넣을 수 없습니다.";
			NEKey& key = static_cast<NEKey&>(source);

			result = kcs.insert(index, key);
		}
		break;
	}

	return (NEResult::hasError(result)) ? "ERROR: 삽입 도중 에러가 발생했습니다." : "";
}

NE::NEString RunCommand::execute(const NEStringSet& parameters)
{
	NEEventHandler& handler = Editor::getInstance().getEventHandler();
	type_count	max_frame_count = 0,
		frame_count = 0;

	if(parameters.getLength() > 0)
	{
		if(parameters[0] == "-new")
			handler.initiateTest();
		else 
			max_frame_count = parameters[0].toInt();
	}
	else
		handler.resumeTest();

	cout << "CANCLE키를 누르면 언제든 중단 가능합니다.\n";

	char inputed = 0;
	while(inputed != LG::CANCEL)
	{
		frame_count++;
		if(max_frame_count > 0 && frame_count > max_frame_count)
			break;

		Kernal::getInstance().getNodeManager().execute();		 

		if(_kbhit())
			inputed = _getch();
	}

	handler.pauseTest();
	cout << frame_count << " 프레임 진행하였다.\n";
	return "";
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

	NEEventHandler& handler = Editor::getInstance().getEventHandler();
	if(NEResult::hasError(handler.loadScriptFile(NETString(parameters[0]))))
		return "ERROR: 파일 로드 실패.";

	return "";
}
NE::NEString NewCommand::execute(const NEStringSet& parameters)
{
	NEEventHandler& handler = Editor::getInstance().getEventHandler();
	if(NEResult::hasError(handler.initializeNewFile()))
		return "ERROR: 새로운 파일 시작 실패.";

	return "";
}
NE::NEString HelpCommand::execute(const NEStringSet& parameters)
{
	switch(parameters.getLength())
	{
	case 0:
		LG::Core::open(CommandListWindow());
		break;

	case 1:
		if(parameters[0] == "-module")
			LG::Core::open(ModuleEncyclo());		
		break;

	case 2:		
		if(parameters[0] == "-module")
		{
			NEObject& obj = ::Core::getObjectBy(parameters[1]);
			if( ! obj.isSubClassOf(NEType::NEMODULE))
				return NEString("ERROR: 주어진 경로(") + parameters[1] + ")는 모듈이 아닙니다.";

			LG::Core::open(ModuleEncyclo(false, static_cast<NEModule*>(&obj)));
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