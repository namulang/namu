#pragma once

namespace wrd
{
	namespace pref
	{
		template <typename T>
		T& nullref() {
			T* nulled = 0;
			return *nulled;
		}
	}
}
