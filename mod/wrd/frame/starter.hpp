#pragma once

#include "frame.hpp"
#include "../builtin/container/native/tndumMap.hpp"

namespace wrd {

    class _wout starter : public node {
        WRD(CLASS(starter, node))

    public:
        // node:
        nbicontainer& subs() override;

        wbool canRun(const ucontainable& args) const override;
        str run(const ucontainable& args) override;

    private:
        node& _findMain(node& pak, const ucontainable& args);
    };

#include "../common/MSVCHack.hpp"
}
