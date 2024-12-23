#include "frame.hpp"

#include "../ast/baseFunc.hpp"
#include "../ast/dumScope.hpp"
#include "../ast/obj.hpp"
#include "../worker/visitor/visitor.hpp"
#include "thread.hpp"

namespace nm {
    NM(DEF_ME(frame), DEF_VISIT())

    me::frame() { _rel(); }

    me::~frame() { _rel(); }

    void me::add(const scope& existing) { add(nulOf<node>(), existing); }

    void me::add(const nbicontainer& existing) {
        tstr<scope> wrap = scope::wrap<scope>(existing);
        add(*wrap);
    }

    void me::add(const node& owner) { add(owner, owner.subs()); }

    void me::add(const node& owner, const scope& existing) {
        if(nul(existing)) return;
        if(_stack.size() <= 0) return _stack.push_back(scopeRegister{owner, existing}), void();

        tstr<scope> cloned = existing.cloneChain() orRet;
        cloned->getTail().link(*_getTop().s);
        _stack.push_back(scopeRegister{owner, cloned});
        NM_DI("scope added: frame.len[%d] scope.owner[%s]", _stack.size(), owner);
    }

    void me::addLocal(const std::string& name, const node& n) {
        if(_stack.size() <= 0) return NM_E("couldn't push new node. the top scope is null"), void();
        auto &locals =
            getLocals() orRet NM_E("it's tried to add variable into %s. it's not valid.", name),
             void();
        locals.add(name, n);
    }

    node& me::getOwner(const node& sub) {
        if(nul(sub)) return nulOf<node>();

        [[maybe_unused]] const nchar* name = sub.getType().getName().c_str();
        node* lastOwner = nullptr;
        for(auto& reg: _stack) {
            lastOwner = reg.owner ? &reg.owner.get() : lastOwner;
            nbool isOwner = reg.s->in(sub);
            NM_DI("sub[%s] is in owner[%s]? == %s", name, *reg.owner, isOwner);
            if(isOwner) return *lastOwner;
        }

        NM_E("couldn't find owner of %s", sub);
        return nulOf<node>();
    }

    nbool me::setMe(const node& new1) { return _me.bind(new1); }

    void me::setMe() { _me.rel(); }

    node& me::getMe() { return *_me; }

    scope& me::getLocals() {
        auto& top = _getTop();
        if(nul(top) || top.owner) return nulOf<scope>();
        return *top.s;
    }

    void me::del() {
        _stack.pop_back();
        NM_DI("scope deleted. frames.len[%d] thisFrame.len[%d]", thread::get().getFrames().len(),
            _stack.size());
    }

    scopeRegister& me::_getTop() {
        ncnt len = _stack.size();
        if(len <= 0) return nulOf<scopeRegister>();

        return _stack[len - 1];
    }

    nbool me::addFunc(const baseFunc& new1) { return _funcs.add(new1); }

    void me::delFunc() { _funcs.del(); }

    baseFunc& me::getFunc() { return *_funcs.last(); }

    // node:
    scope& me::subs() {
        scopeRegister& reg = _getTop();
        static dumScope inner;
        return nul(reg) ? inner : *reg.s;
    }

    tstr<nbicontainer> me::mySubs() const {
        const auto& top = _getTop();
        return top.owner ? top.owner->mySubs() : top.s->getContainer();
    }

    priorType me::prioritize(const args& a) const { return NO_MATCH; }

    str me::run(const args& a) { return str(); }

    void me::rel() {
        _rel();
        super::rel();
    }

    const std::vector<scopeRegister>& me::getScopeRegisters() const { return _stack; }

    nbool me::setRet(const node& newRet) const { return _ret.bind(newRet); }

    nbool me::setRet() const {
        _ret.rel();
        return true;
    }

    node& me::getRet() const { return *_ret; }

    void me::dump() const {
        nidx n = 0;
        logger& log = logger::get();
        for(const scopeRegister& reg: _stack) {
            const std::string& owner = reg.owner ? reg.owner->getType().getName() : "null";
            log.logBypass("\t\tscope[" + std::to_string(n++) + "]: owner is " + owner);

            const auto& subs = *reg.s;
            nidx n2 = 0;
            for(auto e = subs.begin(); e; ++e)
                log.logBypass("\t\t\tsub[" + std::to_string(n2++) + "]: " + e.getKey() + " " +
                    e.getVal().getType().getName());
        }
    }

    void me::_rel() {
        _me.rel();
        _funcs.rel();
        _stack.clear();
        _ret.rel();
    }
} // namespace nm
