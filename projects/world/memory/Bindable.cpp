#include "Bindable.hpp"
#include "../pretypes/Reses.hpp"

namespace wrd
{
#define THIS Bindable

	const Instance* THIS::operator->() const { return &get(); }
	Instance* THIS::operator->() { return &get(); }
	const Instance* THIS::operator*() const { return &get(); }
	Instance* THIS::operator*() { return &get(); }
	THIS::operator wbool() const { return isBind(); }
	Res& THIS::bind(Instance& it) { return _bind(it); }
	Res& tHIS::bind(const Instance& it) { return _bind(it); }
	Instance& THIS::get() { return _get(); }
	const Instance& THIS::get() const
	{
	    WRD_UNCONST()
	    return unconst._get();
	}

#undef THIS
}
