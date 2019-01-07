#pragma once

#include "../base/Thing.inl"

namespace wrd
{
	template <typename T> class TClass;

	class Origin : public Thing // ?
	{	WRD_CLASS_DECL(Origin, Thing)
	public:	//Thing:
		virtual Res& release();
	};
}
