#pragma once

#include "../ast/scope.hpp"
#include "../builtin/container/native/tnchain.inl"

namespace namu {

    class _nout scopeStack : public instance, clonable {
        WRD(CLASS(scopeStack, instance))

    public:
        tstr<scopes>& getTop();
        const tstr<scopes>& getTop() const;
        tstr<scopes>& getBottom();
        const tstr<scopes>& getBottom() const;

        ncnt len() const;
        ncnt chainLen() const;

        nbool push(scopes& new1);

        tstr<scopes> pop();

        void rel();

    private:
        tstr<scopes> _top;
        tstr<scopes> _bottom;
    };
}
