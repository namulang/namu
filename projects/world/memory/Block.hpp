#pragma once

#include "UId.hpp"

namespace wrd
{
    class Block : public Trace
    {	WRD_INHERIT(Block, Trace)
    public: // Block:
        /// increase refcnt.
        Result& look();
        Result& ignore();
        Result& link();
        Result& unlink();
    };
}
