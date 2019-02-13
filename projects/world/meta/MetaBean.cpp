#include "MetaBean.hpp"

namespace wrd
{
#define THIS MetaBean
	const wchar* THIS::_getDemangledName(const wchar* org)
	{
		static wchar* demangled = NULL;
		if(demangled)
			free(demangled);
		int status = 0;
		return demangled = abi::__cxa_demangle(org, 0, 0, &status);
	}
}
