#include "State.hpp"
#include "../meta.hpp"
#include "../pretypes.hpp"

namespace wrd
{
#define THIS State
	WRD_CLASS_DEF(THIS)

	THIS::THIS() { THIS::release(); }
	const wbool& THIS::isInit() const { return _is_init; }

	Res& THIS::init()
	{
		WRD_ASSERT(isInit(), wascancel)
		return _setInit(true);
	}

	Res& THIS::release() { return _setInit(false); }

	Res& THIS::_setInit(wbool new1)
	{
		(wbool&) isInit() = new1;
		return wasgood;
	}
}
