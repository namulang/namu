#pragma once

#include "Stream.hpp"

namespace wrd { namespace clog {

    class ConsoleStream : public Stream {
        WRD_DECL_THIS(ConsoleStream, Stream)

    public:
        virtual const char* getName() const;
        virtual wbool dump(const char* message);
    };
} }
