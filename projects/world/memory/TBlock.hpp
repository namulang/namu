#pragma once

#include "Block.hpp"
#include "../base/TGettable.hpp"

namespace wrd
{
    template <typename T>
    class TBlock : public TGettable<T, Block>
    {  WRD_CLASS(TBlock, TGettable)
    public:

    };
}
