#pragma once

#include "../../ast/point.hpp"

namespace wrd {

	struct fail : public area {
		enum type {
			ERR = 0,
			WARN,
		};

		fail(const point& s, const point& e, fail::type t)
			: area({s, e}), fType(t) {}

		fail::type fType;
	};
}
