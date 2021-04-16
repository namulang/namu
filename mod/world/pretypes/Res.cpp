#include "Res.hpp"
#include "../meta.hpp"

namespace wrd
{
#define ME Res

	WRD_CLASS_DEF(ME)
	
	ME::operator wbool() const { return isErr(); }
	//	TODO: all below funcs.
	wbool ME::isErr() const { return ! isGood(); }
	//	TODO: imple these funcs.
	Res& ME::warn(...) { return wasgood; }
	Res& ME::err(...) { return wasgood; }
	Res& ME::info(...) { return wasgood; };
	Res& ME::dbg(...) { return wasgood; };

#undef ME
}
