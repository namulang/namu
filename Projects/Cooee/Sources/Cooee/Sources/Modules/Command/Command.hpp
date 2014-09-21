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
	virtual NEString execute(const NEStringSet& parameters);
};

class CloseCommand : public Command
{
public:
	CloseCommand() : Command("close cls",
		"현재 윈도우를 닫습니다.\n"
		"별칭	: close, cls\n"
		"사용법	: close") {}
	virtual NEString execute(const NEStringSet& parameters);
};

class VersionCommand : public Command
{
public:
	VersionCommand() : Command("version ver",
		"현재 버전을 확인한다.\n"
		"별칭	: version, ver\n"
		"사용법	: version") {}
	virtual NEString execute(const NEStringSet& parameters);
};

class PlanetarizeCommand : public Command
{
public:
	PlanetarizeCommand() : Command("planetarium pln",
		"스크립트 전체 구조를 비추는 플라네타리움을 띄운다\n"
		"별칭	: planetarium, pln\n"
		"사용법	: planetarium\n"
		"		  planetarium <초점을 잡을 경로>") {}
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
	virtual NEString execute(const NEStringSet& parameters);
};


class AddCommand : public Command
{
public:
	AddCommand(const NEString& names, const NEString& help)
		: Command(names, help) {}
	AddCommand() : Command("add ad",
		"주어진 경로에 새로운 개체를 하나 추가한다.\n"
		"별칭	: add, ad\n"
		"사용법	: add -node <추가할 NodeCodeSet/Key의 경로>\n"
		"		  add -module <추가할 모듈의 이름> <개발자> <revision> <추가할 ModuleCodeSet/Key의 경로>\n"
		"		  add -key <추가할 키의 이름> <추가할 KeyCodeSet의 경로>") {}
	virtual NEString execute(const NEStringSet& parameters);
};
class OrphanCommand : public Command
{
public:
	OrphanCommand(const NEString& names, const NEString& help)
		: Command(names, help) {}

	NEString _searchParent(const NEString& full_path, type_index& index_to_insert, NEObject** parent_to_insert);
};
class PasteCommand : public OrphanCommand
{
public:
	PasteCommand() : OrphanCommand("paste, p",
		"미리 예약해둔 경로를 복사하여, 특정 경로에 붙여넣는다. 원본과 붙여넣을 경로의 타입이 일치되어야 한다.\n"
		"별칭	: paste, p\n"
		"사용법	: paste <붙여넣을 경로>") {}
	virtual NEString execute(const NEStringSet& parameters);
};
class DeleteCommand : public OrphanCommand
{
public:
	DeleteCommand() : OrphanCommand("delete d",
		"주어진 경로에 위치한 개체를 삭제한다.\n"
		"별칭	: delete, d\n"
		"사용법	: delete <경로>") {}
	virtual NEString execute(const NEStringSet& parameters);
};