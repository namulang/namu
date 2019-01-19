#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
    union Id
    {
		struct SeperatedId
		{
			wuint blk_n:21;
			wuint chk_n:22;
			wuint serial:21;
		} sep;
		wint64 num;
		
		Id(wint64 it = WRD_INDEX_ERROR);
		Id(wuint new_blk_n, wuint new_chk_n, wuint new_serial);
    };
}
