#pragma once

#include "node.hpp"

namespace namu {

    class _nout mockNode : public node {
        NAMU(ME(mockNode, node), VISIT())
        friend class exprMaker;

    public:
        mockNode();
        mockNode(const node& org);

    public:
        const ntype& getType() const override;

        using super::subs;
        scope& subs() override;

        priorType prioritize(const args& a) const override;

        str run(const args& a) override;

        clonable* clone() const override;

        nbool isComplete() const override;

        node& getTarget();
        const node& getTarget() const NAMU_UNCONST_FUNC(getTarget());

        const src& getSrc() const override;

        void* cast(const type& to) override;

    protected:
        void _setSrc(const src& s) override;

    private:
        str _org;
    };
}
