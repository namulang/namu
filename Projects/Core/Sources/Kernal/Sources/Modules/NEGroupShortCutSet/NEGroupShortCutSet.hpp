#pragma once

#include "../NEShortCutSet/NEShortCutSet.hpp"

namespace NE
{
	class NE_DLL NEGroupShortCutSet : public NEShortCutSet
	{
	public:
		typedef NEShortCutSet SuperClass;
		typedef NEGroupShortCutSet ThisClass;

	public:
		NEGroupShortCutSet();
		NEGroupShortCutSet(type_index size);
		NEGroupShortCutSet(const ThisClass& source);

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