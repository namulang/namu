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

        nbool canRun(const args& a) const override;
        str run(const args& a) override;

    private:
        node& _findMain(node& pak, const args& a);
    };

#include "../common/MSVCHack.hpp"
}
