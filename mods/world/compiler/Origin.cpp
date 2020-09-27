#include "Origin.hpp"
#include "../base/Thing.hpp"
#include "../meta.hpp"

namespace wrd
{
#define THIS Origin
	WRD_CLASS_DEF(THIS)

	Res& THIS::release()
	{
		//TODO?:
		return wasgood;
	}
}
