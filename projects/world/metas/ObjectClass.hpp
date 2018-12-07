#pragma once

#include "Class.hpp"

namespace wrd
{
	class Array;
	template <typename T> class TStrong;
	class ObjectClass : public Class
	{
	public:
		virtual const Array& getVars() const;

	private:
		TStrong<Array> _vars;
	};
}
