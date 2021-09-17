#pragma once

#include "../../common.hpp"

namespace wrd {

	class asable {
	public:
		virtual wbool is(const type& to) const = 0;
		virtual str as(const node& from, const type& to) const = 0;
	};

    typedef std::vector<asable*> asables;
}
