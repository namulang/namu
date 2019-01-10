#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
    union Id
    {
		struct SeperatedId
		{
		    wuint cls:21;
		    wuint idx:21;
			wuint chk_n:14;
			wuint blk_n:8;
			wuint serial:21;
		} sep;
		wint64 num;
		
		Id(wint64 it = WRD_INDEX_ERROR) : num(it) {}
		Id(wuint itscls, wuint itschk_n, wuint itsblk_n, wuint itsserial) : sep {itscls, itschk_n, itsblk_n, itsserial} {}
    };
}
