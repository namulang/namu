#pragma once

#include "../../ast/clonable.hpp"
#include "../../type/wtype.hpp"

namespace namu {
    class _wout srcSupply : public instance, public clonable {
        WRD(ADT(srcSupply, instance))

    public:
        /// @return true if there is no more data to process.
        virtual wbool next() = 0;
        virtual const char* get() const = 0;
        /// return to first cursor.
        virtual void ret() = 0;
    };
}
