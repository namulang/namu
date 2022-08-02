#pragma once

#include "frame.hpp"
#include "../builtin/container/native/tndumMap.hpp"
#include "../ast/slot.hpp"

namespace namu {

    class _nout starter : public node {
        WRD(CLASS(starter, node))

    public:
        // node:
        nbicontainer& subs() override;

        nbool canRun(const ucontainable& args) const override;
        str run(const ucontainable& args) override;

    private:
        node& _findMain(node& pak, const ucontainable& args);
    };

#include "../common/MSVCHack.hpp"
}
