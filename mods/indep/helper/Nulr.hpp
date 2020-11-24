#pragma once

namespace wrd {
	///	means null-reference.
	template <typename T>
	T& nulr() {
		T* ret = 0;
		return *ret;
	}
}

