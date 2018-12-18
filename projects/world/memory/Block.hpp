#pragma once

#include "../bases/Id.hpp"

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

      protected:
              virtual Instance& _get();
    };
}
