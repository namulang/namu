#pragma once

#include "frame.hpp"
#include "../builtin/container/native/tndumMap.hpp"
#include "../ast/slot.hpp"

namespace namu {

    class _nout starter : public node {
        NAMU(CLASS(starter, node))

    public:
        // node:
        nbicontainer& subs() override;

        str run(const args& a) override;

        nbool canRun(const args& a) const override;

    private:
        node& _findMain(node& pak, const args& a);
    };
}
