#pragma once

#include "./wrd-commons.hpp"
#include "./base.hpp"
#include "./memory.hpp"
#include "./msg-usr.hpp"
#include "./meta.hpp"
#include "./pretypes.hpp"
#include "./container.hpp"

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
