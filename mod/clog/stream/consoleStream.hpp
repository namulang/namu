#pragma once

#include "stream.hpp"

namespace namu {

    class _nout consoleStream : public stream {
        NAMU_ME(consoleStream, stream)

    public:
        consoleStream();

    public:
        //  Stream:
        const char* getName() const override;
        nbool logBypass(const char* message) override;
    };
}
