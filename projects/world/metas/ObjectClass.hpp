#pragma once

#include "../compiler/Origin.hpp"
#include "Class.hpp"

namespace wrd
{
	class Array;
	template <typename T> class TStrong;
	class ObjectClass : public Class
	{	WRD_CLASS_DECLARE(ObjectClass, Class)
	public:
		virtual const Array& getVars() const;

	private:
		TStrong<Array> _vars;
	};
}
