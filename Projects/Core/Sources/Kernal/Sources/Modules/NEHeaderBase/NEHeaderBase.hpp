#pragma once

#include "../NEIdentifier/NEIdentifier.hpp"

namespace NE
{
	class NE_DLL NEHeader : public NEIdentifier
	{
		NE_DECLARE_INTERFACE(NEHeader, NEIdentifier)

	public:
		NEHeader();
		NEHeader(const NEIdentifier& identifier);

	public:
		virtual ~NEHeader();

	public:
		const NETString& getComment() const;

	};
}