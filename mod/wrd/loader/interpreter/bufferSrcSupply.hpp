#pragma once

#include "srcSupply.hpp"

namespace wrd {
    class _wout bufferSrcSupply : public srcSupply {
        WRD(CLASS(bufferSrcSupply, srcSupply))

    public:
        bufferSrcSupply(const std::vector<string>& buf);

    public:
        wbool next() override;
        const char* get() const override;
        void ret() override;

    private:
        std::vector<string> _srcs;
        int _cursor;
    };
}
