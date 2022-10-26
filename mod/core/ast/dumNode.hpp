#pragma once

#include "node.hpp"

namespace namu {

    class dumNode : public node {
        NAMU(ME(dumNode, node), VISIT())

    public:
        const ntype& getType() const override {
            return ttype<node>::get();
        }

        using super::subs;
        nbicontainer& subs() override;

        nbool canRun(const args& a) const override { return false; }

        str run(const args& a) override { return str(); }

        clonable* clone() const override {
            return new me(*this);
        }
    };
}
