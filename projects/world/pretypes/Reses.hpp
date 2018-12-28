#pragma once

#include "Res.hpp"

namespace wrd
{
#define _DECL(classname)								\
	class _result_ ## classname : public Res			\
	{	WRD_CLASS_DECL(_result_ ## classname, Res)	\
	public:												\
	} classname;

	WRD_EACH(_DECL,
		wasnull, wassuperfail, wasconst, wascancel, waswrongargs, wasfuncfail, wasgood, wasdup,
		wasbindfail, wasntneed, waswrongtype, waswrongdata, wasfileio, waswrongmember, waswrongop
	)


#undef _DECL
}
