#pragma once

#include "../../../ast/baseFunc.hpp"
#include "../../../ast/params.hpp"

namespace nm {

    template <typename T> class _nout printFunc: public baseFunc {
        NM(CLASS(printFunc, baseFunc))

    public:
        const params& getParams() const override {
            static params inner(*new param("msg", new T()));
            return inner;
        }

        str getRet() const override {
            static str inner(new T());
            return inner;
        }

        str run(const args& a) override {
            const params& ps = getParams();
            if(a.len() != ps.len())
                return NM_E("length of args(%d) and typs(%d) doesn't match.", a.len(), ps.len()),
                       nullptr;

            const node& org = ps[0].getOrigin();
            tstr<T> evaluated = a[0].asImpli(*org.as<T>());
            if(!evaluated)
                return NM_E("evaluation of arg[%s] -> param[%s] has been failed.", a[0], org),
                       str();

            std::cout << evaluated->get();
            return evaluated;
        }
    };
}
