#pragma once

#include "../NEObject/NEObject.hpp"

namespace NE
{
	class NE_DLL NEMatcher : public NEObject
	{
		NE_DECLARE_INTERFACE_ONLY(NEMatcher, NEObject)

	public:
		virtual type_bool operator()() const = 0;

	public:
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual type_result isValid() const;
	};
}