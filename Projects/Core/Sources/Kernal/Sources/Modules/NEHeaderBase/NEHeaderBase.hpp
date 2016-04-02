#pragma once

#include "../NEIdentifier/NEIdentifier.hpp"

namespace NE
{
	class NE_DLL NEHeaderBase : public NEIdentifier
	{
		NE_DECLARE_INTERFACE(NEHeaderBase, NEIdentifier)

	public:
		NEHeaderBase();
		NEHeaderBase(const NEIdentifier& identifier);

	public:
		virtual ~NEHeaderBase();

	public:
		const NETString& getComment() const;

	};
}