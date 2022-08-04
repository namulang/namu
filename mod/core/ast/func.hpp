#pragma once

#include "expr.hpp"

namespace namu {

    class param;
    template <typename T, typename TACTIC> class tnarr;
    typedef tnarr<param, strTactic> params;

    class _nout func : public expr {
        NAMU(ADT(func, expr))

    public:
        static inline const std::string ME = "me";

    public:
        nbool canRun(const ucontainable& args) const override;

        /// @return parameters of run() func.
        ///         parameter is just a type. and I don't care about the value of each parameters.
        ///         that is the reason why I uses a ref to represents parameter.
        ///
        ///         I need the name and which types should be casted and binded from given arguments
        ///         are matters.
        virtual const params& getParams() const;

        /// @return node which has same type of the func.
        ///         in namu lang, even type is an object. that's why I return this as a node.
        /// @remark please don't confuse this to evalType.
        ///         evaluate means program just read the code and expand or calculate then replace
        ///         it to the accurate another identifier or variable. so evalType of the func is
        ///         just the func itself because there is nothing to calculate or run.
        ///         that's completely different to Return type of the function.
        ///         if there is a runExpr instance, and it takes the func and proper argument,
        ///         then it can be evaluated and its evalType is the return type of the func.
        virtual const node& getRet() const = 0;
    };

    typedef tnarr<func> funcs;
}
