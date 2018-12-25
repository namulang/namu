#pragma once

#include "../bases/Id.hpp"

namespace wrd
{
    class Block : public Trace
    {	WRD_CLASS_DECLARE(Block, Trace)
    public: // Block:
        /// increase refcnt.
        Res& look();
        Res& ignore();
        Res& link();
        Res& unlink();

      protected:
              virtual Instance& _get();
    };
}
