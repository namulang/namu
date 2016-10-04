#pragma once

#include "../NELengthedObject/NELengthedObject.hpp"

namespace NE
{
	class NE_DLL NEIteratorBase : public NELengthedObject
	{
		NE_DECLARE_INTERFACE_ONLY(NEIteratorBase, NELengthedObject)

	public:
		This& operator++();	//	doesn't support postfix overloading.
		This& operator--();
		type_bool operator==(const This& rhs) const;
		type_bool operator!=(const This& rhs) const;
		This& operator+=(type_count step_for_next);
		This& operator-=(type_count step_for_next);

	public:
		///	@brief	checks that this iterator reaches to the end of iterating.
		/// @return	returns true when iterator reaches to back of the first iterator,
		///			or next of the last iterator¤Ñthe end iterator.
		virtual type_bool isEnd() const = 0;
		virtual type_result next(type_count step_for_next) = 0;
		virtual type_result back(type_count step_for_back) = 0;

	public:
		type_result next();
		type_result back();
	};
}
