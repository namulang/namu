#pragma once

#include "../NEShortCutSet/NEShortCutSet.hpp"

namespace NE
{
	class NE_DLL NEPriorityShortCutSet : public NEShortCutSet
	{
	public:
		typedef NEShortCutSet SuperClass;
		typedef NEPriorityShortCutSet ThisClass;

	public:
		NEPriorityShortCutSet();
		NEPriorityShortCutSet(type_index size);
		NEPriorityShortCutSet(const ThisClass& source);

	public:
		const ThisClass& operator+=(const ThisClass& source);
		ThisClass operator+(const ThisClass& source) const;

	public:
		virtual type_result _enlist(NENode& node, type_index index);
		virtual type_result _unlist(NENode& node, type_index index);

	protected:
		type_index _getEnlistedIndex(NEShortCut& shortcut, type_index node_real_index);
	};
}