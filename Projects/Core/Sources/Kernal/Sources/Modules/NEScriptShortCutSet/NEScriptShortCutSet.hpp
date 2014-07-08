#pragma once

#include "../NEShortCutSet/NEShortCutSet.hpp"

namespace NE
{
	class NE_DLL NEScriptShortCutSet : public NEShortCutSet
	{
	public:
		typedef NEShortCutSet SuperClass;
		typedef NEScriptShortCutSet ThisClass;

	public:
		NEScriptShortCutSet();
		NEScriptShortCutSet(type_index size);
		NEScriptShortCutSet(const ThisClass& source);

	public:
		const ThisClass& operator+=(const ThisClass& source);
		ThisClass operator+(const ThisClass& source) const;

	public:
		virtual type_result _enlist(NENode& node, type_index index);
		virtual type_result _unlist(NENode& node, type_index index);
	};
}