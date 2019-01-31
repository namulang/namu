#pragma once

#include "Info.hpp"
#include "Err.hpp"

namespace wrd
{
#define _CLASS(base, classname)							\
	class _result_ ## classname : public base 			\
	{	WRD_CLASS_DECL(_result_ ## classname, base)		\
	public:												\
	};
#define _DECL(base, cls) 		\
	_CLASS(base, cls)			\
	extern _result_ ## cls cls;

	#include "Reses.in"

#undef _DECL
#undef _CLASS
}
