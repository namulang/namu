#include "NELengthedObject.hpp"
#include "../NETClass/NETClass.hpp"

namespace NE
{
	NE_DEFINE_INTERFACE_ONLY(NELengthedObject)

	type_index NELengthedObject::getLengthLastIndex() const
	{
		return getLength() - 1;
	}
}