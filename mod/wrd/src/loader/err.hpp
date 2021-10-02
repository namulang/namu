#pragma once

#include "../ast/point.hpp"

namespace wrd {

	struct err: public area {
		enum type {
			ERR = 0,
			WARN,
		};

		err(const point& s, const point& e, err::type t)
			: area({s, e}), fType(t) {}

		err::type fType;
	};
}
