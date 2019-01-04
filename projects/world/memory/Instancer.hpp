#pragma once

#include "../base/Manager.hpp"
#include "../bind/TBindable.hpp"

namespace wrd
{
	class Instancer : public Manager
	{	WRD_CLASS(Instancer, Manager)
	public:
		const Block& operator[](Id id) const;
		const Block& operator[](widx cls, widx idx) const;

	public:
		//	Instancer:
		const Block& get(Id id) const;
		Block& get(Id id) const;
		template <typename T> T& get() { return get().cast<T>(); }
		virtual Res& bind(Instance& new1);
		virtual Res& unbind(Instance& old);

	private:
		Blocks _blocks;
	};
}
