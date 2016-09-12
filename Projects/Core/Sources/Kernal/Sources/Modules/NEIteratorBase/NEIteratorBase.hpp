#pragma once

#include "../NELengthedObject/NELengthedObject.hpp"

namespace NE
{
	class NE_DLL NEIteratorBase : public NELengthedObject
	{
		NE_DECLARE_INTERFACE_ONLY(NEIteratorBase, NELengthedObject)

	public:
		This& operator++();	//	doesn't support postfix overloading.
		This& operator+(type_count step_for_next);
		type_bool operator==(const This& rhs) const;
		type_bool operator!=(const This& rhs) const;

	public:
		virtual type_bool isEnd() const = 0;
		virtual type_result next(type_count step_for_next) = 0;

	public:
		type_result next();
	};
}
