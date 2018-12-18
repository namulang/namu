#pragma once

#pragma message "1"
#include "./wrd-commons.hpp"
#pragma message "4"
#include "./binds.hpp"
#pragma message "5"
#include "./metas.hpp"
#pragma message "2"
#include "./bases.hpp"
#pragma message "3"
#include "./memory.hpp"
#pragma message "6"
#include "./msg-usrs.hpp"
#pragma message "7"
#include "./pretypes.hpp"

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
