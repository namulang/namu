#include "Res.hpp"
#include "../meta.hpp"

namespace wrd
{
#define THIS Res

	WRD_CLASS_DEF(THIS)
	
	THIS::operator wbool() const { return isErr(); }
	//	TODO: all below funcs.
	wbool THIS::isErr() const { return false; }
	wbool THIS::isWarn() const { return false; }
	wbool THIS::isInfo() const { return false; };
	//	TODO: imple these funcs.
	Res& THIS::warn(...) { return wasgood; }
	Res& THIS::err(...) { return wasgood; }
	Res& THIS::info(...) { return wasgood; };
	Res& THIS::dbg(...) { return wasgood; };

#undef THIS
}
