#pragma once

#include "expr.hpp"

namespace wrd {

    class func : public expr {
        WRD(INTERFACE(func, expr))

    public:
        explicit func(const std::string& name): _name(name) {}

        using super::subs;
        nucontainer& subs() override {
            static narr empty;
            return empty;
        }

        using super::run;
        str run(const ucontainable& args) override;

        wbool canRun(const ucontainable& typs) const override;

        const std::string& getName() const override { return _name; }
        // modifying name of func is not permitted.

    protected:
        virtual str _onCastArgs(narr& castedArgs) = 0;

    private:
        tstr<narr> _asArgs(const ucontainable& args);

    private:
        std::string _name;
    };

    typedef tnarr<func> funcs;
}
