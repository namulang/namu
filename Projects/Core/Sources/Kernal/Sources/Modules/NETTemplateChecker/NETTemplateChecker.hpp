#pragma once

#include "../NETypeChecker/NETypeChecker.hpp"

namespace NE
{
	template <typename T>
	class NETTemplateChecker : public NETypeChecker
	{
	private:
		template <template<typename> class Template, typename T>
		static yes _isTemplate(Template<T>*);
		static no _isTemplate(...);

	public:
		static const type_bool IS_TEMPLATE = sizeof(_isTemplate((T*)0)) == sizeof(yes);
	};
}