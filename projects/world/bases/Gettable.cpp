#include "Gettable.hpp"

namespace wrd
{
#define THIS Gettable
      typedef THIS This; //TODO: remove this

      const Instance& THIS::get() const
      {
              WRD_UNCONST_THIS()
              return unconst->_get();
      }

      Instance& THIS::get() { return _get(); }

#undef THIS
}
