#pragma once

#include "../bases/TGettable.inl"

namespace wrd
{
    class Result;
	class Instance;

	template <typename S=void>
    class TBindable : public TGettable<Instance, S>
    {	WRD_CLASS_DECLARE_2(TBindable<S>, TGettable<Instance WRD_COMMA() S>)
    public:
        operator wbool() const;

    public:
        virtual Result& bind(Instance& new1) = 0;
		template <typename V>
		Result& bind(TBindable<V>& rhs);
        /// mostly, unbind is replacable to release() comletely.
        /// but some class(e.g. Refer) treat differently between unbind() and release().
        Result& bind(Instance* new1);
        virtual Result& unbind() = 0;
        virtual wbool isBind() const = 0;
    };
}

