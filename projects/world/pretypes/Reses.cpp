#include "Reses.hpp"
#include "../meta.hpp"

namespace wrd
{
#define _DECL(cls) 					\
	WRD_CLASS_DEF(_result_ ## cls)	\
	_result_ ## cls cls;

	#include "Reses.in"

#undef _DECL
}
