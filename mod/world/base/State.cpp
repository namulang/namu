#include "State.hpp"
#include "../meta.hpp"
#include "../pretypes.hpp"

namespace wrd
{
#define ME State
	WRD_CLASS_DEF(ME)

	ME::ME() { ME::release(); }
	const wbool& ME::isInit() const { return _is_init; }

	Res& ME::init()
	{
		WRD_ASSERT(isInit(), wascancel)
		return _setInit(true);
	}

	Res& ME::release() { return _setInit(false); }

	Res& ME::_setInit(wbool new1)
	{
		(wbool&) isInit() = new1;
		return wasgood;
	}
}
