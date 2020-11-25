#pragma once

#include "../pref-commons.hpp"

namespace wrd
{
	namespace pref
	{
		class Object
		{	WRD_DECL_THIS(Object)
		public:
			virtual wbool release() = 0;
			virtual Object& clone() const = 0;
			wbool isNull() const;
		};
	}
}
