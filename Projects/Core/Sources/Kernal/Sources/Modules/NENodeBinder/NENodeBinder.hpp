#pragma once

#include "../NEBinderBase/NEBinderBase.hpp"

namespace NE
{
	class NEIndexedNodeSet;

	class NE_DLL NENodeBinder : public NEBinderBase
	{
		NE_DECLARE_CLASS(NENodeBinder, NEBinderBase)

		friend class NENodeSelector;

	public:
		NENodeBinder();
		NENodeBinder(const NENode& node/*, NEType::Type manager_type*/);

	public:
		virtual type_bool isBinded() const;

	public:
		NENode& getBinded();
		const NENode& getBinded() const;
		type_result bind(const NENode& node/*, NEType::Type manager_type*/);

	private:
		NEIndexedNodeSet& _getNodeSet();
		const NEIndexedNodeSet& _getNodeSet() const;
	};
}