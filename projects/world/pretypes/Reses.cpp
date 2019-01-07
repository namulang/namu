#include "Reses.hpp"

namespace wrd
{
#define _DECL(cls) _result_ ## cls cls;

	#include "Reses.in"

#undef _DECL
}
