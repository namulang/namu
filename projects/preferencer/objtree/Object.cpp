#include "Object.hpp"

namespace wrd
{
	namespace pref
	{
#define THIS Object
		wbool THIS::isNull() const { return ! this; }
	}
}
