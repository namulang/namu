#include "Lengthable.hpp"

namespace wrd
{
#define THIS Lengthable

	wbool THIS::isFull() const { return getLen() >= getSize(); }
	wbool THIS::isCapable() const { return getLen() < getSize(); }
}
