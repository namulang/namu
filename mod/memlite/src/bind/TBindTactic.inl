#include "TBindTactic.hpp"

namespace wrd {

#define TEMPL template <typename T>
#define THIS TBindTactic<T>

    TEMPL Type& THIS::getType() {
        return TType<T>::get();
    }

#undef THIS
#undef TEMPL
}
