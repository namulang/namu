#pragma once

#include "../../Includes/Includes.hpp"

class Command : public NEObject {
public:
	Command(const NEString& names_delimetered_with_space, const NEString& new_help);
	NEStringSet names;
	NEString help;
	virtual NEString execute(const NEStringSet& parameters) = 0;
	virtual type_result isValid() const;
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
	virtual void release();
	bool operator!=(const Command& rhs) const;
};

class ListCommand : public Command
{
public:
	ListCommand();
	FUNC_CLONE(ListCommand)
	virtual NEString execute(const NEStringSet& parameters);
};

class CloseCommand : public Command
{
public:
	CloseCommand() : Command("close cls",
		"현재 윈도우를 닫습니다.\n"
		"별칭	: close, cls\n"
		"사용법	: close") {}
	FUNC_CLONE(CloseCommand)
	virtual NEString execute(const NEStringSet& parameters);
};

class VersionCommand : public Command
{
public:
	VersionCommand() : Command("version ver v",
		"현재 버전을 확인한다.\n"
		"별칭	: version, ver, v\n"
		"사용법	: version") {}
	FUNC_CLONE(VersionCommand)
	virtual NEString execute(const NEStringSet& parameters);
};

class PlanetarizeCommand : public Command
{
public:
	PlanetarizeCommand() : Command("planetarium pln pl",
		"스크립트 전체 구조를 비추는 플라네타리움을 띄운다\n"
		"별칭	: planetarium, pl, pln\n"
		"사용법	: planetarium\n"
		"		  planetarium <초점을 잡을 경로>") {}
	FUNC_CLONE(PlanetarizeCommand)
	virtual NEString execute(const NEStringSet& parameters);
};

class CopyCommand : public Command
{
public:
	CopyCommand() : Command("copy cp",
		"복사할 경로를 예약해둔다. paste 명령어를 이 경로를 복사한다.\n"
		"별칭	: copy, cp\n"
		"사용법	: copy <원본 경로>\n"
		"		  copy <원본 경로> <복사될 경로>") {}
	FUNC_CLONE(CopyCommand)
	virtual NEString execute(const NEStringSet& parameters);
};
class CutCommand : public Command
{
public:
	CutCommand() : Command("cut",
		"잘라낼 경로를 예약해둔다. paste 명령어를 이 경로를 복사하고 원본을 삭제한다.\n"
		"별칭	: cut\n"
		"사용법	: cut<원본 경로>\n"
		"		  cut <원본 경로> <복사될 경로>") {}
	FUNC_CLONE(CutCommand)
		virtual NEString execute(const NEStringSet& parameters);
};

class OrphanCommand : public Command
{
public:
	OrphanCommand(const NEString& names, const NEString& help)
		: Command(names, help) {}
	NEString _searchParent(const NEString& full_path, type_index& index_to_insert, NEObject** parent_to_insert);
};
class AddCommand : public OrphanCommand
{
public:
	AddCommand(const NEString& names, const NEString& help)
		: OrphanCommand(names, help) {}
	AddCommand() : OrphanCommand("add a",
		"주어진 경로에 새로운 개체를 하나 추가한다.\n"
		"별칭	: add, a\n"
		"사용법	: add -node <추가할 NodeCodeSet/Key의 경로>\n"
		"		  add -module <추가할 모듈의 이름> <개발자> <revision> <추가할 ModuleCodeSet/Key의 경로>\n"
		"		  add -key <추가할 키의 이름> <추가할 KeyCodeSet의 경로>") {}
	FUNC_CLONE(AddCommand)
	virtual NEString execute(const NEStringSet& parameters);
private:
	NEType::Type _findKeyTypeBy(const NEString& type_name);
};
class PasteCommand : public OrphanCommand
{
public:
	PasteCommand() : OrphanCommand("paste p",
		"미리 예약해둔 경로를 복사하여, 특정 경로에 붙여넣는다. 원본과 붙여넣을 경로의 타입이 일치되어야 한다.\n"
		"별칭	: paste, p\n"
		"사용법	: paste <붙여넣을 경로>/<붙여넣을 인덱스>") {}
	FUNC_CLONE(PasteCommand)
	virtual NEString execute(const NEStringSet& parameters);
};
class DeleteCommand : public OrphanCommand
{
public:
	DeleteCommand() : OrphanCommand("delete d",
		"주어진 경로에 위치한 개체를 삭제한다.\n"
		"별칭	: delete, d\n"
		"사용법	: delete <경로>") {}
	FUNC_CLONE(DeleteCommand)
	virtual NEString execute(const NEStringSet& parameters);
};
class RunCommand : public Command
{
public:
	RunCommand() : Command("run r",
		"현재의 스크립트를 실행(테스트) 한다. CANCLE키를 누르면 실행을 중단 할 수 있다.\n"
		"별칭	: run, r\n"
		"사용법	: run (이전에 중단한 부분부터 다시 실행한다)\n"
		"		  run <반복할 프레임 카운트>\n"
		"		  run -new (처음부터 다시 실행한다)") {}
	FUNC_CLONE(RunCommand)
	virtual NEString execute(const NEStringSet& parameters);
};
class SaveCommand : public Command
{
public:
	SaveCommand() : Command("save s",
		"현재의 스크립트를 파일로 저장한다. 저장할 디렉토리는 정해져 있다.\n"
		"별칭	: save, s\n"
		"사용법	: save <저장할 파일명>\n"
		"		  save (이 스크립트의 파일명으로 저장된다)") {}
	FUNC_CLONE(SaveCommand)
	virtual NEString execute(const NEStringSet& parameters);
};
class LoadCommand : public Command
{
public:
	LoadCommand() : Command("load l",
		"스크립트를 파일로부터 불러들인다. 디버깅 중인 테스트는 초기화된다.\n"
		"별칭	: load, l\n"
		"사용법	: load <읽어들일 파일명>") {}
	FUNC_CLONE(LoadCommand)
	virtual NEString execute(const NEStringSet& parameters);
};
class NewCommand : public Command
{
public:
	NewCommand() : Command("new",
		"작성중인 스크립트를 없애고 새로 시작한다.\n"
		"별칭	: new, n\n"
		"사용법	: new") {}
	FUNC_CLONE(NewCommand)
	virtual NEString execute(const NEStringSet& parameters);
};
class HelpCommand : public Command
{
public:
	HelpCommand() : Command("help h",
		"도움말 사전을 연다. 모듈 백과사전과 명령어 사전을 열 수 있다.\n"
		"별칭	: help\n"
		"사용법	: help (명령어들을 열람한다)\n"
		"		: help -module\n"
		"		: help -module <모듈명>") {}
	FUNC_CLONE(HelpCommand)
	virtual NEString execute(const NEStringSet& parameters);
};
class HeaderCommand : public Command
{
public:
	HeaderCommand() : Command("header head hd",
		"스크립트 헤더를 수정할 수 있는 화면을 연다.\n"
		"별칭	: header, head, hd\n"
		"사용법	: header") {}
	FUNC_CLONE(HeaderCommand)
	virtual NEString execute(const NEStringSet& parameters);
};
class ObserveCommand : public Command
{
public:
	ObserveCommand() : Command("observe ob",
		"현재 화면에 보여지는 구조를, 작성중인 스크립트와 "
		"실행중인 영역 중 어떤 것을 보여줄지 지정한다.\n"
		"별칭	: observe, ob\n"
		"사용법	: observe	(스크립트, 실행영역을 번갈아가며 전환)\n"
		"		  observe -debug (실행영역으로 전환)\n"
		"		  observe -script (스크립트 영역으로 전환)") {}
	FUNC_CLONE(ObserveCommand)
		virtual NEString execute(const NEStringSet& parameters);
	void _markDeletionToAllWindows();
};