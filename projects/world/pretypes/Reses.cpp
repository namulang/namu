#include "Reses.hpp"
#include "../meta.hpp"

namespace wrd
{
#define _DECL(base, cls) 			\
	WRD_CLASS_DEF(_result_ ## cls)	\
	_result_ ## cls cls;

	#include "Reses.in"

#undef _DECL
}
