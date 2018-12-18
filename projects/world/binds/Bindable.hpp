#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
    class Result;
	class Instance;

    class Bindable
    {
    public:
        operator wbool() const;

    public:
        virtual Result& bind(Instance& new1) = 0;
        /// mostly, unbind is replacable to release() comletely.
        /// but some class(e.g. Refer) treat differently between unbind() and release().
        Result& bind(Instance* new1);
        virtual Result& unbind() = 0;
        virtual wbool isBind() const = 0;
    };
}
