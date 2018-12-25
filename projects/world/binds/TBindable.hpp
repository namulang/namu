#include "TBindable.inl"
#include "../metas/TClass.hpp"
#include "../pretypes/Reses.hpp"

namespace wrd
{
#define TEMPL template <typename S>
#define THIS TBindable<S>

	WRD_CLASS_DEFINE(TEMPL, THIS)

    TEMPL THIS::operator wbool() const { return isBind(); }

    TEMPL Res& THIS::bind(Instance* new1)
    {
        WRD_IS_NULL(*new1)
        return bind(*new1);
    }

#undef THIS
#undef TEMPL
}
