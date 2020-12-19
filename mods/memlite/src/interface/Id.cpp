#include "Id.hpp"

namespace wrd { namespace memlite {

	Id::Id(wint64 it) : num(it) {}
	Id::Id(wint newTagN, wint newChkN, wuint newSerial) : s {newTagN, newChkN, newSerial} {}
}}
