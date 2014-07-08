#pragma once

#include "../NEBinderBase/NEBinderBase.hpp"

namespace NE
{
	class NEIndexedNodeSet;

	class NE_DLL NENodeBinder : public NEBinderBase
	{
		typedef NENodeBinder ThisClass;
		typedef NEBinderBase SuperClass;

		friend class NENodeSelector;

	public:
		NENodeBinder();
		NENodeBinder(const NENode& node, NEType::Type manager_type);

	public:
		virtual bool isBinded() const;

	public:
		virtual NEObject& clone() const;
		virtual NEType::Type getType() const;

	public:
		NENode& getBinded();
		const NENode& getBinded() const;
		type_result bind(const NENode& node, NEType::Type manager_type);

	private:
		NEIndexedNodeSet& _getNodeSet();
		const NEIndexedNodeSet& _getNodeSet() const;
	};
}