#pragma once

#include "stream.hpp"

namespace wrd {

    class consoleStream : public stream {
        WRD_DECL_THIS(consoleStream, stream)

    public:
        //  Stream:
        const char* getName() const override;
        wbool dump(const char* message) override;
    };
}
