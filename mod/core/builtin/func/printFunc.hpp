#pragma once

#include "../../ast/func.hpp"

namespace namu {

    template <typename T>
    class _nout printFunc : public func {
        NAMU(CLASS(printFunc, func))

    public:
        const params& getParams() const override {
            static params inner(*new param("msg", new T()));
            return inner;
        }

        const node& getRet() const override {
            static T inner;
            return inner;
        }

        str run(const args& a) override {
            const params& ps = getParams();
            if(a.len() != ps.len())
                return NAMU_E("length of args(%d) and typs(%d) doesn't match.", a.len(), ps.len()), nullptr;

            const node& org = ps[0].getOrigin();
            tstr<T> evaluated = a[0].as(*org.as<T>());
            if(!evaluated)
                return NAMU_E("evaluation of arg[%s] -> param[%s] has been failed.", a[0].getType().getName().c_str(),
                        org.getType().getName().c_str()), str();

            std::cout << evaluated->get();
            return evaluated;
        }
   };
}
