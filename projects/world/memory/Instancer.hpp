#pragma once

#include "../msg-usr/Manager.hpp"
#include "Pool.hpp"
#include "Akashic.hpp"
#include "TStrong.hpp"

namespace wrd
{
	class Instancer : public Manager
	{	WRD_CLASS_DECL(Instancer, Manager)
		friend class Instance;
	public:
		//	Instancer:
		Res& bind(Instance& new1);
		Res& unbind(Instance& old);
		const Pool& getPool() const;
		const Akashic& getAkashic() const;

	private:
		void* _new1(size_t sz);
		void _del(void* pt, wcnt sz);
		wbool _hasInstanceBlock(const Instance& it) const;

	private:
		Pool _pool;
		Akashic _akashic;
	};
}
