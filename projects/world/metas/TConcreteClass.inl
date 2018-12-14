#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
    class Instance;
    template <typename T> class TStrong;

    template <typename T, typename S>
    class TConcreteClass : public S
    {	WRD_CLASS(TConcreteClass, S)
    public:
        virtual TStrong<Instance> instance() const;
    };
}
