#pragma once

#include "../NELengthedObject/NELengthedObject.hpp"

namespace NE
{
	class NE_DLL NEIteratorBase : public NELengthedObject
	{
		NE_DECLARE_INTERFACE_ONLY(NEIteratorBase, NELengthedObject)

	public:
		This& operator++();
		This& operator+(type_count step_for_next);
		//	doesn't support postfix overloading.

	public:
		const NEObject& get() const = 0;
		virtual NEObject& get() = 0;
		virtual type_bool isEnd() const = 0;
		virtual type_result next(type_count step_for_next = 1) = 0;
	};
}
