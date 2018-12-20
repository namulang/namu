#pragma once

#include "Refer.hpp"

namespace wrd
{
      template <typename T>
      class TRefer : public TGettable<T, Refer>
      {      WRD_CLASS_2(TRefer, TGettable<T WRD_COMMA() Refer>)
      };
}
