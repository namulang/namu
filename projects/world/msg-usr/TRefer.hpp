#pragma once

#include "Refer.hpp"

namespace wrd
{
	template <typename T>
	class TRefer : public TGettable<T, Refer>
	{	WRD_CLASS_2(TRefer, TGettable<T WRD_COMMA() Refer>)
	public:
		using Super::operator=;
		template <typename V> This& operator=(const TBindable<V>& rhs) {
			Super::operator=(rhs);
			return *this;
		}
		template <typename V> This& operator=(TBindable<V>& rhs) {
			Super::operator=(rhs);
			return *this;
		}
	};           
}                
                 
