#pragma once

#include "./wrd-commons.hpp"
#include "./bases.hpp"
#include "./memory.hpp"
#include "./binds.hpp"
#include "./metas.hpp"
#include "./msg-usrs.hpp"
#include "./pretypes.hpp"

namespace wrd
{
    class World : public Manager
    {
        typedef World This;

    private:
        World();

    public:
        virtual ~World();

    public:
        static This& get() {
            static This inner;
            return inner;
        }
    };
}
