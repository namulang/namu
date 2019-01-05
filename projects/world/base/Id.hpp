#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
    union Id
    {
		struct SeperatedId
		{
		    widx cls:21;
		    widx idx:21;
			wcnt serial:21;
		} sep;
		wint64 num;
		
		Id(wint64 it = WRD_INDEX_ERROR) : num(it) {}
		Id(widx itscls, widx itsidx, wcnt itsserial) : sep {itscls, itsidx, itsserial} {}
    };
}
