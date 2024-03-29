#pragma once

#include "node.hpp"

namespace namu {

    class _nout mockNode : public node {
        NAMU(ME(mockNode, node), VISIT())

    public:
        mockNode();
        mockNode(const node& org);

    public:
        const ntype& getType() const override;

        using super::subs;
        nbicontainer& subs() override;

        priority prioritize(const args& a) const override;

        str run(const args& a) override;

        str getEval() const override;

        clonable* clone() const override;

        nbool isComplete() const override;

    private:
        str _org;
    };
}
