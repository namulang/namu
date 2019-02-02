#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
    union Id
    {
		struct SeperatedId
		{
			wint blk_n:21;
			wint chk_n:22;
			wuint serial:21;
		} sep;
		wint64 num;
		
		Id(wint64 it);
		Id(wint new_blk_n = WRD_INDEX_ERROR, wint new_chk_n = WRD_INDEX_ERROR, wuint new_serial = WRD_DUMMY);
    };
}
