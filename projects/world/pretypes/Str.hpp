#pragma once

#include "../containers/TArray.inl"

namespace wrd
{
	//TODO: imple this class
	class Str : public TArray<wchar>
	{	WRD_CLASS_DECL(Str, TArray<wchar>)
	public:
		Str() {}
		Str(const wchar* org) : _str(org) {}

	public:
		Str& operator=(const wchar* org) {
			_str = org;
			return *this;
		}
		const char* toCStr() const { return _str.c_str(); }
		//	TODO: reuse not to redifine below func.
		//	Lengthable:
		virtual wcnt getSize() const { return _str.size(); } 
		virtual wcnt getLen() const { return _str.size(); } 

		std::string _str;
	};
}
