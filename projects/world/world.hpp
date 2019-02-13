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
		//	World:
		Instancer& getInstancer();
		const Instancer& getInstancer() const;
		Classer& getClasser();
		const Classer& getClasser() const;
		//	State:
		virtual Res& init();

	private:
		Instancer _instancer;
		Classer _classer;

    public:
        static World& get();
    };
}
