#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
    class Instance;
    template <typename T> class TStrong;

    template <typename T, typename S>
    class TInterfaceClass : public S
    {	WRD_CLASS(TInterfaceClass, S)
    public:
        virtual TStrong<Instance> instance() const;
    };
}
