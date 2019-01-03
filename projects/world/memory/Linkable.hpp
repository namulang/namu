#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
	class Res;

	class Linkable
	{
	public:
		Res& link(Instance& it);
		Res& unlink(Instance& it);
	};
