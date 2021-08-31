#pragma once

#include "../../common/dep.hpp"

namespace wrd {
	struct point {
		wcnt row;
		wcnt col;
	};

	struct area {
		point start;
		point end;
	};
}
