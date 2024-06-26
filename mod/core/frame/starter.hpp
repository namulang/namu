#pragma once

#include "../ast/origin.hpp"
#include "../loader/worker/worker.inl"
#include "defaultSigZone.hpp"

namespace nm {
    class frames;

    class _nout starter: public worker<str, args> {
        typedef worker<str, args> __super8;
        NM(CLASS(starter, __super8))

    public:
        enum logFlag3 {
            LOG_STRUCTURE = 1 << 7,
            LOG_GRAPH_ON_EX = 1 << 8
        };

    public:
        static inline const std::string MAIN = "main";

    public:
        me& setPack(obj& pak);
        obj& getPack();
        const obj& getPack() const NM_CONST_FUNC(getPack())

    protected:
        str _onWork() override;
        void _prepare() override;

    private:
        node& _findMain(obj& pak, const args& a);
        void _prepareFrame(frames& fr);
        str _postprocess(str res);

    private:
        tstr<obj> _pak;
    };
}
