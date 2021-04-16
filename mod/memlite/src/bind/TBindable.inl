#include "TBindable.hpp"

namespace wrd {

#define TEMPL template <typename T>
#define ME TBindable<T>

	TEMPL T* ME::operator->() { return &get(); }
	TEMPL T& ME::operator*() { return get(); }
	TEMPL ME::operator wbool() const { return isBind(); }

	TEMPL wbool ME::canBind(const T& it) const {
        WRD_NUL(it, false)
	    return canBind(it.getType());
	}

#undef ME
#undef TEMPL
}
