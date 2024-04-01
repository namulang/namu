#pragma once

#include "../builtin/container/native/tnchain.hpp"
#include "immutableTactic.hpp"
#include "node.hpp"

namespace namu {
    class _nout scope : public tnmap<std::string, node, immutableTactic> {
        typedef tnmap<std::string, node, immutableTactic> __super1;
        NAMU(CLASS(scope, __super1))

    public:
        scope();
        scope(const node& owner);

    public:
        node& getOwner() override;
        void setOwner(const node& owner) override;
        me* deepClone() const override;

    private:
        weak _owner;
    };
}
