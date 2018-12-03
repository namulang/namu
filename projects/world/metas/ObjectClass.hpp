#pragma once

#include "Class.hpp"

namespace wrd
{
	class Array;
	template <typename T> class TStrong;
	class ObjectClass : public Class
	{
	public:
		virtual const Array& getVariables() const;

	private:
		TStrong<Array> _vars;
	};
}
