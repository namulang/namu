#include "delayRule.hpp"
#include "../../builtin/container/native/tndumMap.hpp"

namespace namu {

    template <typename C1, typename C2, typename R1, typename R2>
    nbicontainer& delayRule<C1, C2, R1, R2>::subs() {
        static ndumMap inner;
        return inner;
    }

    template <typename C2, typename R1, typename R2>
    nbicontainer& delayRule<void, C2, R1, R2>::subs() {
        static ndumMap inner;
        return inner;
    }

    template <typename C1, typename R1, typename R2>
    nbicontainer& delayRule<C1, void, R1, R2>::subs() {
        static ndumMap inner;
        return inner;
    }

    template <typename R1, typename R2>
    nbicontainer& delayRule<void, void, R1, R2>::subs() {
        static ndumMap inner;
        return inner;
    }
}
