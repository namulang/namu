#pragma once

#include "../NEObject/NEObject.hpp"

namespace NE
{
	class NE_DLL NEIdableObject : public NEObject
	{
	public:
		typedef NEIdableObject This;
		typedef NEObject Super;

	public:
		virtual type_id getId() const = 0;
	};
}