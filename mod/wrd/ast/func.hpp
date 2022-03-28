#pragma once

#include "expr.hpp"

namespace wrd {

    class func : public expr {
        WRD(INTERFACE(func, expr))

    public:
        using super::run;
        str run(const ucontainable& args) override;

        wbool canRun(const ucontainable& typs) const override;

    protected:
        virtual str _onCastArgs(narr& castedArgs) = 0;

    private:
        tstr<narr> _asArgs(const ucontainable& args);
    };

    typedef tnarr<func> funcs;
}
