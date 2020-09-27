#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
	///	@remark	TClass is a class template using monostate pattern.
	///			so it duplicates all static variables on each modules and it causes that can't 
	///			check hierarchy properly.
	///			sure, I can exports them,template classes, as external symbol for 3rd party modules to link
	///			and make it act well. but this requires user to declare another macro or statements such as
	///			burden to get them be annoy.
	///			instead of that, I put those inside of static symbols at normal nested private class.
	///			now, TClass of course will be duplicated on each modules and code bloated but it will act
	///			like proxy pointing	this nested class.
	///
	///			in conclusion, users can ignore this background reasons and use WRD_CLASS macro without
	///			additional consideration.
	class MetaBean
	{
	protected:
		static const wchar* _getDemangledName(const wchar* org);
	};
}
