#pragma once

#include "node.hpp"

namespace namu {

    class dumNode : public node {
        NAMU(ME(dumNode, node), VISIT())

    public:
        const ntype& getType() const override;

        using super::subs;
        nbicontainer& subs() override;

        priority prioritize(const args& a) const override;

        str run(const args& a) override;

        clonable* clone() const override;
    };
}
