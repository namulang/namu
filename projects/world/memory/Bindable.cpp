#include "Bindable.hpp"
#include "../pretypes/Reses.hpp"

namespace wrd
{
#define THIS Bindable

	const Instance* THIS::operator->() const { return &get(); }
	Instance* THIS::operator->() { return &get(); }
	const Instance& THIS::operator*() const { return get(); }
	Instance& THIS::operator*() { return get(); }
	THIS::operator wbool() const { return isBind(); }
	Res& THIS::bind(const Instance& it) { return _bind(it); }

	wbool THIS::canBind(const Instance& it)
	{
		WRD_IS_NULL(it, false)
		return canBind(it.getClass());
	}

	Instance& THIS::get() { return _get(); }

	const Instance& THIS::get() const
	{
	    WRD_UNCONST()
	    return unconst._get();
	}

#undef THIS
}
