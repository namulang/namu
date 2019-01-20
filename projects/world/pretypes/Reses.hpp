#pragma once

#include "Res.hpp"

namespace wrd
{
#define _CLASS(classname)								\
	class _result_ ## classname : public Res			\
	{	WRD_CLASS_DECL(_result_ ## classname, Res)		\
	public:												\
	};
#define _DECL(cls) 				\
	_CLASS(cls)					\
	extern _result_ ## cls cls;

	#include "Reses.in"

#undef _DECL
#undef _CLASS
}
