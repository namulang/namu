#pragma once

#include "../base/Manager.hpp"

namespace wrd
{
      class Instancer : public Manager
      {      WRD_CLASS(Instancer, Manager)
      public:
		  const Block& get(Id id) const;
		  const Block& operator[](Id id) const;

      private:
		  Blocks _blocks;
      };
}
