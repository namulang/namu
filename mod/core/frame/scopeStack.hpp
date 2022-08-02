#pragma once

#include "../ast/scope.hpp"
#include "../builtin/container/native/tnchain.inl"

namespace namu {

    class _wout scopeStack : public instance, clonable {
        WRD(CLASS(scopeStack, instance))

    public:
        tstr<scopes>& getTop();
        const tstr<scopes>& getTop() const;
        tstr<scopes>& getBottom();
        const tstr<scopes>& getBottom() const;

        wcnt len() const;
        wcnt chainLen() const;

        wbool push(scopes& new1);

        tstr<scopes> pop();

        void rel();

    private:
        tstr<scopes> _top;
        tstr<scopes> _bottom;
    };
}
