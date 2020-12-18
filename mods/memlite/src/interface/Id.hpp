#pragma once

#include "../common.hpp"

namespace wrd { namespace memlite {

    union Id {

		struct SeperatedId {
			wint tagN:21;
			wint chkN:22;
			wuint serial:21;
		} s;
		wint64 num;

		Id(wint64 it);
		Id(wint new_tagN = WRD_INDEX_ERROR, wint newChkN = WRD_INDEX_ERROR, wuint newSerial = 0);
    };
}}
