#include "callstack.hpp"
#include "../builtin/container/native/tnarr.inl"
#include "../builtin/container/native/tnchain.inl"
#include "../ast/scopes.hpp"
#include "../ast/src/src.hpp"
#include "../ast/baseFunc.hpp"
#include "../ast/params.hpp"

namespace namu {

    calltrace::calltrace() {}
    calltrace::calltrace(const tnchain<std::string, node, scope>& scope) {
        it.bind(scope.getOwner());
        if(it) {
            const src& s = it->getSrc();
            at = s.getName();
            const baseFunc& cast = it->cast<baseFunc>();
            if(!nul(cast))
                at += "(" + cast.getParams().toStr() + ")";

            in = s.getFile().getFileName() + ":" + std::to_string(s.getPos().row);
        }
    }

    NAMU(DEF_ME(callstack))

    nbicontainer::iter me::begin() const {
        if(!_stack) return nbicontainer::iter();
        return _stack->begin();
    }

    const calltraces& me::getTraces() const {
        if(!_traces) {
            calltraces* ret = new calltraces();
            const tnchain<std::string, node, scope>* e = _stack ? &_stack.get() : nullptr;
            while(e) {
                ret->add(new calltrace(*e));
                e = &e->getNext();
            }
            _traces.bind(ret);
        }
        return *_traces;
    }

    void me::dump() const {
        for(const auto& c : getTraces())
            NAMU_E("\tat %s in %s", c.at.c_str(), c.in.c_str());
    }

    void me::setStack(const scopes& stack) {
        _stack.bind(stack);
        _traces.rel();
    }
}
