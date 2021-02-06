#include "TBindTactic.hpp"

namespace wrd {

#define TEMPL template <typename T>
#define THIS TBindTactic<T>

    TEMPL const Type& THIS::getType() const {
        return TType<T>::get();
    }

    TEMPL wbool THIS::isConst() const { return false; }

#undef THIS
#define THIS TBindTactic<const T>

    TEMPL const Type& THIS::getType() const {
        return TType<T>::get();
    }

    TEMPL wbool THIS::isConst() const { return true; }

#undef TEMPL
#undef THIS
}
