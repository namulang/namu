#include "Id.hpp"

namespace wrd { namespace memlite {

    WRD_DEF_THIS(Id)

	This::Id(wint64 it) : num(it) {}
	This::Id(wint newTagN, wint newChkN, wuint newSerial) : s {newTagN, newChkN, newSerial} {}
}}
