#pragma once

#include "UId.hpp"

namespace wrd
{
    class Block : public Trace
    {
    public: // Block:
        /// increase refcnt.
        Result& look();
        Result& ignore();
        Result& link();
        Result& unlink();
    };
}
