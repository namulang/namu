#pragma once

#include "expr.hpp"

namespace wrd {

    class param;
    template <typename T, typename TACTIC> class tnarr;
    typedef tnarr<param, strTactic> params;

    class func : public expr {
        WRD(INTERFACE(func, expr))

    public:
        wbool canRun(const ucontainable& args) const override;

        /// @return parameters of run() func.
        ///         parameter is just a type. and I don't care about the value of each parameters.
        ///         that is the reason why I uses a ref to represents parameter.
        ///
        ///         I need the name and which types should be casted and binded from given arguments
        ///         are matters.
        virtual const params& getParams() const {
            static params inner;
            return inner;
        }
    };

    typedef tnarr<func> funcs;
}
