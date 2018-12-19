#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
	class Class;
	class Instance;
	template <typename T> class TStrong;
	template <typename T> class TClass;

    template <typename T, typename S = void>
    class TBindable : public S
    {  WRD_CLASS_DECLARE(TBindable, S)
    public:
        const T* operator->() const;
        T* operator->();
        const T* operator*() const;
        T* operator*();
    };
    template <typename T>
    class TBindable<T, void>
    {
    public:
        const T* operator->() const;
        T* operator->();
        const T* operator*() const;
        T* operator*();
    };
}
