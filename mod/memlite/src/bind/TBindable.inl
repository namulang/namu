#include "TBindable.hpp"

namespace wrd {

#define TEMPL template <typename T>
#define THIS TBindable<T>

	TEMPL T* THIS::operator->() { return &get(); }
	TEMPL T& THIS::operator*() { return get(); }
	TEMPL THIS::operator wbool() const { return isBind(); }

	TEMPL wbool THIS::canBind(const T& it) const {
        WRD_NUL(it, false)
	    return canBind(it.getType());
	}

#undef THIS
#undef TEMPL
}
