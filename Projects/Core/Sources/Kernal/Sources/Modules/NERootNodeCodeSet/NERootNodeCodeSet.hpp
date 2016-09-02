#pragma once

#include "../NENodeCodeSet/NENodeCodeSet.hpp"

namespace NE
{
	class NE_DLL NERootNodeCodeSet : public NENodeCodeSet
	{
		NE_DECLARE_INTERFACE(NERootNodeCodeSet, NENodeCodeSet)

	public:
		NERootNodeCodeSet(NEEnlistableManager& manager);
		NERootNodeCodeSet(type_index size);
		NERootNodeCodeSet(const NERootNodeCodeSet& source);

	public:
		virtual ~NERootNodeCodeSet();

	public:
		const NERootNodeCodeSet& operator+=(const NERootNodeCodeSet& source);
		NERootNodeCodeSet operator+(const NERootNodeCodeSet& source) const;

	protected:
		virtual type_result _onEnlisted(NENode& node);
	};
}