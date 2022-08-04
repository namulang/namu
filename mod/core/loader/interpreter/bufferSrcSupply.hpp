#pragma once

#include "srcSupply.hpp"

namespace namu {
    class _nout bufferSrcSupply : public srcSupply {
        NAMU(CLASS(bufferSrcSupply, srcSupply))

    public:
        bufferSrcSupply(const std::vector<string>& buf);

    public:
        nbool next() override;
        const char* get() const override;
        void ret() override;

    private:
        std::vector<string> _srcs;
        int _cursor;
    };
}
