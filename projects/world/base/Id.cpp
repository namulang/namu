#include "Id.hpp"

namespace wrd
{
#define THIS Id

	THIS::THIS(wint64 it = WRD_INDEX_ERROR) : num(it) {}
	THIS::THIS(wuint new_blk_n, wuint new_chk_n, wuint new_serial) : sep {new_blk_n, new_chk_n, new_serial} {}
}
