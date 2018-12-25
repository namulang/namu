#include "TBindable.inl"
#include "../metas/TClass.hpp"

namespace wrd
{
#define TEMPL template <typename S>
#define THIS TBindable<S>

	WRD_CLASS_DEFINE(TEMPL, THIS)

    THIS::operator wbool() const { return isBind(); }
    TEMPL Result& THIS::bind(This& rhs) { return bind(rhs._get()); }
	template <typename V> Result& THIS::bind(TBindable<V>& rhs) { return bind(rhs.get()); }

    Result& THIS::bind(Instance* new1)
    {
        WRD_IS_NULL(new1)
        return bind(*new1);
    }

#undef THIS
#undef TEMPL
}
