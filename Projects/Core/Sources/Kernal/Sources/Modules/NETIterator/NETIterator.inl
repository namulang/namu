#pragma once

#include "../NEIteratorBase/NEIteratorBase.hpp"

namespace NE
{
	template <typename T>
	class NETIterator : public NEIteratorBase 
	{
		NE_DECLARE_INTERFACE_ONLY(NETIterator, NEIteratorBase)

	public:
		T& operator*();
		const T& operator*() const;
		T& operator->();
		const T& operator->() const;
	};
}