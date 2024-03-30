#pragma once

#include "../builtin/container/native/tnchain.hpp"
#include "immutableTactic.hpp"
#include "node.hpp"

namespace namu {
    class _nout scope : public tnmap<std::string, node, immutableTactic> {
        typedef tnmap<std::string, node, immutableTactic> __super;
        NAMU(CLASS(scope, __super))

    public:
        scope() {}
        scope(const node& owner): _owner(owner) {}

    public:
        node& getOwner() override { return *_owner; }
        void setOwner(const node& owner) override { _owner.bind(owner); }
        me* deepClone() const override { return (me*) super::deepClone(); }

    private:
        weak _owner;
    };

    class dumScope : public scope {
        NAMU(CLASS(dumScope, scope))

    public:
        dumScope() {}
        dumScope(const node& owner): super(owner) {}
        dumScope(const super& rhs): super(rhs) {} // initialization is allowed.

    public:
        // add:
        using super::add;
        nbool add(const std::string& key, const node& val) override { return false; }

        me* deepClone() const override { return (me*) super::deepClone(); }
    };

    class _nout scopes : public tnchain<std::string, node, scope> {
        typedef tnchain<std::string, node, scope> __super;
        NAMU(CLASS(scopes, __super))

    public:
        scopes();
        explicit scopes(const super::super& arr): super(arr) {}
        explicit scopes(const super::super* arr): super(arr) {}

    public:
        node& getOwner() override { return *_owner; }
        void setOwner(const node& owner) override { _owner.bind(owner); }
        me* deepClone() const override { return (me*) super::deepClone(); }

        using super::wrap;
        me* wrap(const super::super& toShallowWrap) const override { return (me*) _wrap<me>(toShallowWrap); }
        using super::wrapDeep;
        virtual me* wrapDeep(const super::super& toDeepWrap) const override { return (me*) _wrapDeep<me>(toDeepWrap); }
        
    private:
        weak _owner;
    };
}
