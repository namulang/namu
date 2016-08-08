#pragma once

#include "../NEObject/NEObject.hpp"

namespace NE
{
	class NE_DLL NEIdableObject : public NEObject
	{
	public:
		typedef NEIdableObject This;
		typedef NEObject Super;
		typedef NETInterface<This>	MetaClass;

	public:
		virtual const NEClassBase& getClass() const	{ return getClassStatically();	}

	public:
		static const NEClassBase& getClassStatically();

	public:
		virtual type_id getId() const = 0;
	};
}