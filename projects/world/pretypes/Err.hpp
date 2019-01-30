#pragma once

#include "Res.hpp"

namespace wrd
{
	class Err : public Result
	{	WRD_CLASS_DECL(Err, Result)
	public:
		virtual wbool isGood() const { return false; }
	};
}
