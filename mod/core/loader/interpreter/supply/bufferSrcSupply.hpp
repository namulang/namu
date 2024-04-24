#pragma once

#include "srcSupply.hpp"

namespace namu {
    class _nout bufferSrcSupply : public srcSupply {
        NAMU(CLASS(bufferSrcSupply, srcSupply))

    public:
        bufferSrcSupply(const std::string& buf);

    public:
        const std::string& onSupplySrc(parser& ps) const override;

    private:
        std::string _buf;
    };
}
