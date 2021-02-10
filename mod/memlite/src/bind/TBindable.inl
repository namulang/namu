#include "TBindable.hpp"

namespace wrd {

#define TEMPL template <typename T>
#define THIS TBindable<T>

	TEMPL T* THIS::operator->() { return &get(); }
	TEMPL T& THIS::operator*() { return get(); }
	TEMPL THIS::operator wbool() { return isBind(); }
	//TEMPL wbool THIS::bind(T& it) { return _bind(it); }

	TEMPL wbool THIS::canBind(T& it) {
        WRD_NUL(it, false)
	    return canBind(it.getType());
	}

	TEMPL T& THIS::get() { return _get(); }

#undef THIS
#undef TEMPL
}
