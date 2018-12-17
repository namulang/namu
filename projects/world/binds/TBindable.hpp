#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
	class Class;
	class Instance;
	template <typename T> class TStrong;
	template <typename T> class TClass;

    template <typename T, typename S>
    class TBindable : public S
    {  WRD_CLASS(TBindable, S)
    public:
        const T* operator->() const { return &get(); }
        T* operator->() { return &get(); }
        const T* operator*() const { return &get(); }
        T* operator*() { return &get(); }
    };
}
