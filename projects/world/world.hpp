#pragma once

#include "./wrd-commons.hpp"
#include "./base.hpp"
#include "./memory.hpp"
#include "./msg-usr.hpp"
#include "./meta.hpp"
#include "./pretypes.hpp"
#include "./containers.hpp"

namespace wrd
{
    class World : public Manager
    {	WRD_CLASS(World, Manager)
	public: // TODO: block to private:
        World();

	public:
		Instancer& getInstancer();
		const Instancer& getInstancer() const;

	private:
		Instancer _instancer;

    public:
        static WRD_LAZY_METHOD(This, get)
    };
}
