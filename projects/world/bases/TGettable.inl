#pragma once

#include "Gettable.hpp"

namespace wrd
{
    template <typename T, typename S = void>
    class TGettable : public S
    {  WRD_CLASS_DECLARE(TGettable, S)
    public:
        T& get();
        const T& get() const;
    };
	template <typename T>
	class TGettable<T>
	{
	public:
        T& get();
        const T& get() const;
	};
}
