#pragma once

#include "../NEObject/NEObject.hpp"

namespace NE
{
	class NE_DLL NELengthedObject : public NEObject
	{
		NE_DECLARE_INTERFACE_ONLY(NELengthedObject, NEObject)

	public:
		virtual type_index getLength() const = 0;

	public:
		type_index getLengthLastIndex() const;
	};
}