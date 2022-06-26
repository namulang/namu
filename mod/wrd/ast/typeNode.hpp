#pragma once

#include "../ast/node.hpp"

namespace wrd {

    /// typeNode is containing type only.
    /// it does nothing except returning evalType.
    class typeNode : public node {
        WRD(CLASS(typeNode, node))

    public:
        typeNode(const wtype& existType): _type(existType) {}

    public:
        nbicontainer& subs() override;
        wbool canRun(const ucontainable& args) const override { return false; }
        str run(const ucontainable& args) override;
        const wtype& getEvalType() const override;

    private:
        const wtype& _type;
    };
}
