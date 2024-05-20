#pragma once

#include "../loader/worker/worker.inl"
#include "signaler.hpp"

namespace namu {
    class frames;
    class _nout starter : public worker<str, args> {
        typedef worker<str, args> __super8;
        NAMU(CLASS(starter, __super8))

    public:
        static inline const std::string MAIN = "main";

    public:
        me& setPack(node& pak);
        node& getPack();
        const node& getPack() const NAMU_UNCONST_FUNC(getPack())

    protected:
        str _onWork() override;
        void _prepare() override;

    private:
        node& _findMain(node& pak, const args& a);
        void _prepareFrame(frames& fr);
        str _postprocess(str res);
        void _relSignal();
        void _setSignal(void(*fptr)(int));
        void _setSignal();

    private:
        str _pak;
        sigHandler _handler;
    };
}
