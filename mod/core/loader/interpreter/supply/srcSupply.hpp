#pragma once

#include "../../../type/ntype.hpp"
#include "../../../builtin/container/native/tnarr.hpp"

namespace namu {

    class parser;
    class _nout srcSupply : public instance {
        NAMU(ADT(srcSupply, instance))

    public:
        /// @return true if there is no more data to process.
        virtual const std::string& onSupplySrc(parser& ps) const = 0;
    };

    typedef tnarr<srcSupply> srcSupplies;
}
