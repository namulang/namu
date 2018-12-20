#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
	template <typename T> class TStrong;
	class Instance;
	class Class;

    template <typename T, typename S = void>
    class TGettable : public S
    {  WRD_CLASS_DECLARE_2(TGettable<T WRD_COMMA() S>, S)
    public:
        const T* operator->() const;
        T* operator->();
        const T* operator*() const;
        T* operator*();

	public:
        T& get();
        const T& get() const;
    };
	template <typename T>
	class TGettable<T, void>
	{
	public:
        const T* operator->() const;
        T* operator->();
        const T* operator*() const;
        T* operator*();

	public:
        T& get();
        const T& get() const;
	};
}
