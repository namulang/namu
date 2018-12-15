#pragma once

#include "Refer.hpp"
#include "../binds/TBindable.inl"

namespace wrd
{
      template <typename T>
      class TRefer : public TBindable<TGettable<Refer> >
      {      WRD_CLASS(TRefer, TBindable<TGettable<Refer> >)
      };
}
