#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
	class Lengthable
	{
	public:
		virtual wcnt getLen() const = 0;
		virtual wcnt getSize() const = 0;
		wbool isFull() const;
		wbool isCapable() const;
	};
}
