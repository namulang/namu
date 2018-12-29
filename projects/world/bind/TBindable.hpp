#include "TBindable.inl"
#include "../meta/TClass.hpp"
#include "../pretypes/Reses.hpp"

namespace wrd
{
#define TEMPL template <typename S>
#define THIS TBindable<S>

	WRD_CLASS_DEF(TEMPL, THIS)

    TEMPL THIS::operator wbool() const { return isBind(); }

    TEMPL THIS& THIS::operator=(const Instance& new1)
    {
        this->bind(new1);
        return *this;
    }

    TEMPL THIS& THIS::operator=(const Instance* new1)
    {
        this->bind(new1);
        return *this;
    }

    TEMPL Res& THIS::bind(const Instance* new1)
    {
        WRD_IS_NULL(*new1)
        return bind(*new1);
    }

#undef THIS
#undef TEMPL
}
