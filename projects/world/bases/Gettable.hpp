#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
    class Instance;
    class Gettable
    {
    public:
        Instance& get();
        const Instance& get() const;

      private:
        virtual Instance& _get() = 0;
    };
}
