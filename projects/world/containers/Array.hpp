#pragma once

#include "Container.hpp"

namespace wrd
{
	class Array : public Container
	{	WRD_CLASS_DECL(Array, Container)
	public:
		virtual wcnt getSize() const { return 0;}
		virtual wcnt getLen() const { return 0; }
	};
}
