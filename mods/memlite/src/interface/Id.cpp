#include "Id.hpp"

namespace wrd { namespace memlite {

    WRD_DEF_THIS(Id)

	This::Id(wint64 it) : num(it) {}
	This::Id(wint new_tag_n, wint new_chk_n, wuint new_serial) : s {new_tag_n, new_chk_n, new_serial} {}
}}
