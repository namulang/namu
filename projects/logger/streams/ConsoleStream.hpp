#pragma once

#include "Stream.hpp"

namespace wrd
{
    class ConsoleStream : public Stream
    {
    public:
        virtual const char* getName() const;
        virtual wbool dump(const char* message);
    };
}
