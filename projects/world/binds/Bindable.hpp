#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
    class Instance;
    class Result;
    class Bindable
    {
    public:
        operator wbool() const;

    public:
        virtual Result& bind(Instance& new1) = 0;
        Result& bind(Instance* new1);
        virtual Result& unbind() = 0;
        virtual wbool doesBind() const = 0;
		const Instance& get() const;
		Instance& get();

	protected:
		virtual Instance& _get() = 0;
    };
}
