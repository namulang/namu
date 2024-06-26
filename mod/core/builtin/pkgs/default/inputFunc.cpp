#include "inputFunc.hpp"

#include <iostream>

#include "../../primitive/nStr.hpp"
#ifdef __EMSCRIPTEN__
#    include <emscripten/emscripten.h>
#endif

namespace nm {

    NM(DEF_ME(inputFunc))

    const params& me::getParams() const {
        static params inner;
        return inner;
    }

    str me::getRet() const {
        static str inner(new nStr());
        return inner;
    }

    str me::run(const args& a) {
        const params& ps = getParams();
        if(a.len() != ps.len())
            return NM_E("length of args(%d) and typs(%d) doesn't match.", a.len(), ps.len()),
                   nullptr;

        nStr* ret = new nStr();

#ifdef __EMSCRIPTEN__
        ret->get() = emscripten_run_script_string("prompt('input:');");
#else
        std::getline(std::cin, ret->get());
#endif

        return str(ret);
    }
}
