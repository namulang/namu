#include "TBindable.hpp"

namespace wrd {

#define TEMPL template <typename T>
#define THIS TBindable<T>

	TEMPL const T* THIS::operator->() const { return &get(); }
	TEMPL T* THIS::operator->() { return &get(); }
	TEMPL const T& THIS::operator*() const { return get(); }
	TEMPL T& THIS::operator*() { return get(); }
	TEMPL THIS::operator wbool() const { return isBind(); }
	//TEMPL wbool THIS::bind(T& it) { return _bind(it); }

	TEMPL wbool THIS::canBind(const T& it) {
        WRD_NUL(it, false)
	    return canBind(it.getType());
	}

	TEMPL T& THIS::get() { return _get(); }
	TEMPL const T& THIS::get() const WRD_UNCONST_FUNC(_get())

#undef THIS
#undef TEMPL
}
