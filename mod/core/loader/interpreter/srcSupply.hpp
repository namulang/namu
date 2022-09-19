#pragma once

#include "../../type/ntype.hpp"

namespace namu {
    class _nout srcSupply : public instance {
        NAMU(ADT(srcSupply, instance))

    public:
        /// @return true if there is no more data to process.
        virtual nbool next() = 0;
        virtual const char* get() const = 0;
        /// return to first cursor.
        virtual void ret() = 0;
    };
}
