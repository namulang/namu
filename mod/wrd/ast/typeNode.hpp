#pragma once

#include "../ast/baseObj.hpp"

namespace wrd {

    /// typeNode is containing type only.
    /// it does nothing except returning evalType.
    class typeNode : public baseObj {
        WRD(CLASS(typeNode, baseObj))

    public:
        typeNode(const wtype& existType): _type(existType) {}

    public:
        nbicontainer& subs() override;
        wbool canRun(const ucontainable& args) const override { return false; }
        str run(const ucontainable& args) override;
        const wtype& getEval() const override;
        const baseObj& getOrigin() const override { return *this; }

    private:
        const wtype& _type;
    };
}
