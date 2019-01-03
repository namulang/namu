#pragma once

#include "../base/Manager.hpp"
#include "../bind/TBindable.hpp"

namespace wrd
{
	class Instancer : public TBindable<Manager>
	{	WRD_CLASS(Instancer, Manager)
	public:
		const Block& operator[](Id id) const;
		const Block& operator[](widx cls, widx idx) const;

	public:
		const Block& get(Id id) const;
		Res& link(Instance& new1);
		Res& unlink(Instance& new1);
		//	TBindable:
		virtual Res& bind(const Instance& new1);


	private:
		Blocks _blocks;
	};
}
