#include "genericObj.hpp"
#include "../builtin/container/native/tndumMap.hpp"
#include "../loader/interpreter/tverification.hpp"
#include "../loader/interpreter/verification.inl"
#include "../loader/interpreter/verifier.hpp"

namespace namu {

    NAMU_DEF_ME(genericObj)

    nbicontainer& me::subs() {
        static ndumMap inner;
        return inner;
    }



    NAMU_VERIFY(genericObj, iterateGenerics, {
        for(auto e : it._cache)
            verify(*e.second);
    })
}
