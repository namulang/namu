#pragma once

#include "../common.hpp"

namespace wrd {

    class ref;
    class wtype;
	template <typename T>
    struct tas : public asable, public typeProvidable {

	public:
		const type& getType() const {
			return ttype<T>::get();
		}

        wbool is(const type& to) const {
			return getType() == to;
		}
    };
}
