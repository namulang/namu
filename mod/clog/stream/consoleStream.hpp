#pragma once

#include "stream.hpp"

namespace wrd {

    class _wout consoleStream : public stream {
        WRD_DECL_ME(consoleStream, stream)

    public:
        consoleStream(): super(false) {}

    public:
        //  Stream:
        const char* getName() const override;
        wbool dump(const char* message) override;
    };
}
