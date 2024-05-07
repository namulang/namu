#pragma once

#include "../builtin/container/native/tnbicontainer.hpp"
#include "../builtin/container/native/tnarr.hpp"
#include "../type/dumpable.hpp"
#include "../ast/scope.hpp"
#include "../ast/scopes.hpp"

namespace namu {

    class _nout calltrace : public instance {
        NAMU(CLASS(calltrace, instance))

    public:
        calltrace(const tnchain<std::string, node, scope>& scope);
        calltrace();

    public:
        str it;
        std::string at;
        std::string in;
    };
    typedef tnarr<calltrace> calltraces;

    class _nout callstack : public instance, public dumpable {
        NAMU(CLASS(callstack, instance))

    public:
        nbicontainer::iter begin() const;
        const calltraces& getTraces() const;
        void dump() const override;
        void setStack(const scopes& stack);

    private:

    private:
        tstr<scopes> _stack;
        mutable tstr<calltraces> _traces;
    };
}
