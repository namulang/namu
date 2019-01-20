#include "ObjectClass.hpp"
#include "../meta.hpp"
#include "../container/Array.hpp"

namespace wrd
{
#define THIS ObjectClass
	WRD_CLASS_DEF(THIS)

	wbool THIS::operator==(const This& rhs) const
	{	//	TODO:
		return false;
	}
	
	wbool THIS::operator!=(const This& rhs) const { return ! operator==(rhs); }

    const Array& THIS::getVars() const
    {
        WRD_IS_THIS(const Array)
        return *_vars;
    }
}
