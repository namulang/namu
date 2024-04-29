#pragma once

#include "frame.hpp"
#include "../ast/slot.hpp"

namespace namu {
    class frames;
    class _nout starter : public node {
        NAMU(CLASS(starter, node))

    public:
        static inline const std::string MAIN = "main";

    public:
        // node:
        nbicontainer& subs() override;

        str run(const args& a) override;

        priority prioritize(const args& a) const override;

    private:
        node& _findMain(node& pak, const args& a);
        void _prepareFrame(frames& fr);
    };
}
