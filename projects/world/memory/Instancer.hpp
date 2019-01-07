#pragma once

#include "../msg-usr/Manager.hpp"
#include "TStrong.hpp"

namespace wrd
{
	class Instancer : public Manager
	{	WRD_CLASS(Instancer, Manager)
	public:
		const Block& operator[](Id id) const;

	public:
		//	Instancer:
		const Block& get(Id id) const;
		template <typename T> const T& get(Id id) { return get(id).down<const T>(); }
		virtual Res& bind(Instance& new1);
		virtual Res& unbind(Instance& old);

	private:
		// TODO: Blocks _blocks;
	};
}
