#pragma once

#include "../common.hpp"

namespace wrd { namespace memlite {

    union Id {

		struct SeperatedId {
			wint tag_n:21;
			wint chk_n:22;
			wuint serial:21;
		} s;
		wint64 num;

		Id(wint64 it);
		Id(wint new_tag_n = WRD_INDEX_ERROR, wint new_chk_n = WRD_INDEX_ERROR, wuint new_serial = 0);
    };
}}
