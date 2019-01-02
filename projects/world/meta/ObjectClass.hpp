#pragma once

#include "../compiler/Origin.hpp"
#include "Class.hpp"

namespace wrd
{
	class Array;
	template <typename T> class TStrong;
	class ObjectClass : public Class
	{	WRD_CLASS_DECL(ObjectClass, Class)
	public:
		wbool operator==(const This& rhs);
		wbool operator!=(const This& rhs);

	public:
		virtual const Array& getVars() const;

	private:
		TStrong<Array> _vars;
	};
}
