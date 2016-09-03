#include "NEMatcher.hpp"
#include "../NETClass/NETClass.hpp"

namespace NE
{
	NE_DEFINE_INTERFACE_ONLY(NEMatcher)

	void NEMatcher::release() {}
	NEBinaryFileSaver& NEMatcher::serialize(NEBinaryFileSaver& saver) const { return saver; }
	NEBinaryFileLoader& NEMatcher::serialize(NEBinaryFileLoader& loader) { return loader; }
	type_result NEMatcher::isValid() const { return RESULT_SUCCESS; }
}