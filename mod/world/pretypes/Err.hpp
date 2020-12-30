#pragma once

#include "Res.hpp"

namespace wrd
{
	class Err : public Res
	{	WRD_CLASS_DECL(Err, Res)
	public:
		virtual wbool isGood() const { return false; }
	};
}
