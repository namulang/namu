#pragma once

#include "baseObj.hpp"
#include "../frame/frameInteractable.hpp"

namespace nm {

    /// closure is a proxy for a func with captured object scope.
    /// when you input arguments, its object scope was replaced to the captured scope.
    /// so eventually, you don't need to refer any object if you carry a func with closure.
    class _nout closure: public baseObj {
        NM(ME(closure, baseObj), CLONE(closure), VISIT())

    public:
        closure(const baseObj& org, const baseFunc& func);

    public:
        using super::subs;
        scope& subs() override;

        priorType prioritize(const args& a) const override;

        const ntype& getType() const override;

        const modifier& getModifier() const override;

        str run(const args& a) override;

        const baseObj& getOrigin() const override;

        const baseFunc& getFunc() const;

        params& getParams();
        const params& getParams() const NM_CONST_FUNC(getParams())

    private:
        tstr<baseObj> _org;
        tstr<baseFunc> _func;
    };
}
