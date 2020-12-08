#pragma once

#include "../common.hpp"

namespace wrd {
	///	means null-reference.
	template <typename T>
	T& nulr() {
		T* ret = 0;
		return *ret;
	}

    wbool nul(void* any);

    template <typename T>
    wbool nil(T& any) {
        return !&any;
    }
}

