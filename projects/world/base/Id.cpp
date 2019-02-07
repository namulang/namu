#include "Id.hpp"

namespace wrd
{
#define THIS Id

	THIS::THIS(wint64 it) : num(it) {}
	THIS::THIS(wint new_blk_n, wint new_chk_n, wuint new_serial) : s {new_blk_n, new_chk_n, new_serial} {}
}
