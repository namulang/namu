#pragma once

#include "Stream.hpp"

namespace wrd { namespace clog {

    class ConsoleStream : public Stream {
        WRD_DECL_THIS(ConsoleStream, Stream)

    public:
        //  Stream:
        const char* getName() const;
        wbool dump(const char* message);
    };
} }
