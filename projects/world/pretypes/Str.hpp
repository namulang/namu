#pragma once

#include "../containers/TArray.inl"

namespace wrd
{
	//TODO: imple this class
	class Str : public TArray<wchar>
	{	WRD_CLASS_DECL(Str, TArray<wchar>)
	public:
		Str& operator=(const char* org) {
			_str = org;
			return *this;
		}
		const char* toCStr() const { return _str.c_str(); }

		std::string _str;
	};
}
