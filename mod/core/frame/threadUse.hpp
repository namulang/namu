#pragma once

#include "thread.hpp"

namespace namu {
    class _nout threadUse {
        NAMU(ME(threadUse))

    public:
        threadUse();
        threadUse(const node& ast);
        ~threadUse();

    public:
        thread& get();
        const thread& get() const NAMU_UNCONST_FUNC(get())

        void use();
        void rel();

    private:
        thread _thr;
    };
}
