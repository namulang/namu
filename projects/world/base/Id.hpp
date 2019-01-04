#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
    union Id
    {
		struct SeperatedId
		{
		    widx cls; //    í´ëì¤ì ì¢ë¥
		    widx idx; //    í´ë¹ í´ëì¤ ì¸ì¤í´ì¤ ë²¡í°ì ëªë²ì§¸ì¸ê°.typeê³¼ indexë¥¼ ì¡°í©íë©´ ì´ëìë  ê°ì²´ì ì ê·¼í  ì ìë¤.
		} sep;
		wint64 num;
		
		Id(wint64 it = WRD_INDEX_ERROR) : num(it) {}
		Id(widx itscls, widx itsidx) : sep {itscls, itsidx} {}

    };
}
