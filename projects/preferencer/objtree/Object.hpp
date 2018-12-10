#pragma once

#include "../pref-commons.hpp"

namespace wrd
{
	namespace pref
	{
		class Object
		{	WRD_INHERIT(Object)
		public:
			virtual wbool release() = 0;
			virtual Object& clone() const = 0;
			wbool isNull() const;
		};
	}
}
