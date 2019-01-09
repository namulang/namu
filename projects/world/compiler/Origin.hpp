#pragma once

#include "../base/Instance.hpp"

namespace wrd
{
	class Origin : public Instance
	{	WRD_CLASS_DECL(Origin, Instance)
	public:	//Thing:
		virtual Res& release();
	};
}
