#pragma once

#include "./wrd-commons.hpp"
#include "./bases.hpp"
#include "./memory.hpp"
#include "./msg-usrs.hpp"
#include "./metas.hpp"
#include "./binds.hpp"
#include "./pretypes.hpp"
#include "./containers.hpp"

namespace wrd
{
    class World : public Manager
    {	//TODO: WRD_CLASS(World, Manager)
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
