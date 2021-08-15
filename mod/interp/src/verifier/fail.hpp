#pragma once

#include "../ast/point.hpp"

namespace wrd {

	struct fail {
		enum type {
			ERR = 0,
			WARN,
		};

		fail(fail::type t, const point& s, const point& e)
			: fType(t), start(s), end(e) {}

		fail::type fType;
		point start;
		point end;
	};
}
