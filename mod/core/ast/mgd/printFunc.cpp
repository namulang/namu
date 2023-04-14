#include <iostream>
#include "printFunc.hpp"
#include "../../builtin/primitive/nStr.hpp"

namespace namu {

    NAMU(DEF_ME(printFunc))

    const params& me::getParams() const {
        static params inner(*new param("msg", new nStr()));
        return inner;
    }

    const node& me::getRet() const {
        static nStr inner;
        return inner;
    }

    str me::run(const args& a) {
        const params& ps = getParams();
        if(a.len() != ps.len())
            return NAMU_E("length of args(%d) and typs(%d) doesn't match.", a.len(), ps.len()), nullptr;

        const node& org = ps[0].getOrigin();
        tstr<nStr> evaluated = a[0].as(*org.as<nStr>());
        if(!evaluated)
            return NAMU_E("evaluation of arg[%s] -> param[%s] has been failed.", a[0].getType().getName().c_str(),
                    org.getType().getName().c_str()), str();

        std::cout << evaluated->get();
        return evaluated;
    }
}
