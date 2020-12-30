#include "Bindable.hpp"

namespace wrd { namespace memlite {

    WRD_DEF_THIS(Bindable)

	const Instance* This::operator->() const { return &get(); }
	Instance* This::operator->() { return &get(); }
	const Instance& This::operator*() const { return get(); }
	Instance& This::operator*() { return get(); }
	This::operator wbool() const { return isBind(); }
	wbool This::bind(const Instance& it) { return _bind(it); }

	wbool This::canBind(const Instance& it) {
		WRD_NUL(it, false)
		return canBind(it.getType());
	}

	Instance& This::get() { return _get(); }
	const Instance& This::get() const WRD_UNCONST_FUNC(_get())
}}
