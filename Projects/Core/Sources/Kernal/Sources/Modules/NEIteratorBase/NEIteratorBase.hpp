#pragma once

#include "../NELengthedObject/NELengthedObject.hpp"

namespace NE
{
	class NE_DLL NEIteratorBase : public NELengthedObject
	{
		NE_DECLARE_INTERFACE_ONLY(NEIteratorBase, NELengthedObject)

	public:
		This& operator++();
		//	doesn't support postfix overloading.

	public:
		const NEObject& get() const;
		virtual NEObject& get() = 0;
		virtual type_bool isEnd() const = 0;
		virtual type_bool isStart() const = 0;
		virtual NEIteratorBase& next() = 0;
	};
}
