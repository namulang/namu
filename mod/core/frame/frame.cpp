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
        WHEN_NUL(existing).ret();
        if(_stack.size() <= 0)
            return _stack.push_back(scopeRegister{owner, existing, existing}), void();

        tstr<scope> cloned = existing.cloneChain() OR.ret();
        cloned->getTail().link(*_getTop().linkedS);
        _stack.push_back(scopeRegister{owner, existing, cloned});
        NM_DI("scope added: frame.len[%d] scope.owner[%s]", _stack.size(), owner);
    }

    void me::addLocal(const std::string& name, const node& n) {
        WHEN(_stack.size() <= 0).err("couldn't push new node. the top scope is null").ret();
        auto& locals =
            getLocals() OR.err("it's tried to add variable into %s. it's not valid.", name).ret();
        locals.add(name, n);
    }

    scope& me::getScopeHaving(const node& sub) {
        NM_I("getScopeHaving(%s)", sub);
        return _getOwner<scope>(sub, [&](nbool, auto& reg) { return &reg.linkedS.get(); });
    }

    node& me::getMeHaving(const node& sub) {
        NM_I("getMeHaving(%s)", sub);
        nbool found = false;
        return _getOwner<node>(sub, [&](nbool isOwner, scopeRegister& reg) -> node* {
            baseObj& org = reg.owner TO(template cast<baseObj>());
            WHEN(found && !nul(org)).ret(&org);
            WHEN(!isOwner).ret(nullptr);
            found = true;
            return &org; // org can be nullref and returning null let the loop keep searching.
        });
    }

    nbool me::setMe(const node& new1) { return _me.bind(new1); }

    void me::setMe() { _me.rel(); }

    node& me::getMe() { return *_me; }

    scope& me::getLocals() {
        auto& top = _getTop();
        WHEN(nul(top) || top.owner).retNul<scope>();
        return *top.s;
    }

    void me::del() {
        _stack.pop_back();
        NM_DI("scope deleted. frames.len[%d] thisFrame.len[%d]", thread::get().getFrames().len(),
            _stack.size());
    }

    scopeRegister& me::_getTop() {
        ncnt len = _stack.size();
        WHEN(len <= 0).retNul<scopeRegister>();

        return _stack[len - 1];
    }

    nbool me::addFunc(const baseFunc& new1) { return _funcs.add(new1); }

    void me::delFunc() { _funcs.del(); }

    baseFunc& me::getFunc() { return *_funcs.last(); }

    // node:
    scope& me::subs() {
        scopeRegister& reg = _getTop();
        static dumScope inner;
        return nul(reg) ? inner : *reg.linkedS;
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

    template <typename T>
    T& me::_getOwner(const node& toFind, std::function<T*(nbool, scopeRegister&)> cl) {
        WHEN_NUL(toFind).retNul<T>();

        [[maybe_unused]] const nchar* name = toFind.getType().getName().c_str();
        for(auto e = _stack.rbegin(); e != _stack.rend(); ++e) {
            auto& reg = *e;
            nbool has = reg.s->in(toFind);
            NM_DI("`%s` is in `%s` scope? --> %s", name,
                reg.owner ? reg.owner->getSrc().getName() : "{local}", has);
            T* ret = cl(has, reg);
            WHEN(ret).ret(*ret);
        }

        NM_E("couldn't find owner of %s", toFind);
        return nulOf<T>();
    }
} // namespace nm
