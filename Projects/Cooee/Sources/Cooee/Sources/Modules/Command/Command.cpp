#include "Command.hpp"
#include "../Core/Core.hpp"
#include "../Planetarium/Planetarium.hpp"

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
		result = ::Core::setPathToBeCopied(parameters[0]);

	case 2:
		::Core::commander.command("paste " + parameters[1]);
		break;

	default:
		return "ERROR: 경로를 입력하세요";
	}	
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

		const NEKey& source = Kernal::getInstance().getKeyManager().getKey(parameters[1]);
		if( ! &source) return "ERROR: " + parameters[1] + "에 해당하는 키가 없습니다.";
		NEObject& parsed = ::Core::getObjectBy(parameters[2]);
		if( ! &parsed) return "ERROR: 경로가 잘못 됐네요.";

		switch(parsed.getType())
		{
		case NEType::NEKEY_CODESET:
			{
				NEKeyCodeSet& kcs = (NEKeyCodeSet&) kcs;
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

	//NEObject& parsed = 
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
		{
			if(source.getType() != NEType::NENODE)			
				return "ERROR: 주어진 경로에 " + NEString(source.getTypeName()) + "을 넣을 수 없는데 말입니다.";
			NENode& node = static_cast<NENode&>(source);

			if( ! ncs)
				ncs = (NENodeCodeSet*) parent;

			result = ncs->insert(index, node);
		}		
		break;

		//... ModuleCodeSetKey, KeyCodeSetKey도 동일 ...

	}
}