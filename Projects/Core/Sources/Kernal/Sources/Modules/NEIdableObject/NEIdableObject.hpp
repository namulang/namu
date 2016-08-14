#pragma once

#include "../NEObject/NEObject.hpp"

namespace NE
{
	class NE_DLL NEIdableObject : public NEObject
	{
		NE_DECLARE_INTERFACE_ONLY(NEIdableObject, NEObject)

	public:
		virtual type_id getId() const = 0;
	};
}