#pragma once

#include "Res.hpp"

namespace wrd
{
	class Info : public Res
	{	WRD_CLASS_DECL(Info, Res)
	public:
		virtual wbool isGood() const { return true; }
	};
}
