#pragma warning(push)
#pragma warning(disable: 4146)

#include "NETArgument.hpp"
#include "../NEIntKey/NEIntKey.hpp"

namespace NE
{
	template
	class NE_DLL NETLimitedArgument<NEBooleanSetKey>;
	template
	class NE_DLL NETLimitedArgument<NEByteSetKey>;
	template
	class NE_DLL NETLimitedArgument<NEUByteSetKey>;
	template
	class NE_DLL NETLimitedArgument<NEShortSetKey>;
	template
	class NE_DLL NETLimitedArgument<NEUShortSetKey>;
	template
	class NE_DLL NETLimitedArgument<NEIntSetKey>;
	template
	class NE_DLL NETLimitedArgument<NEUIntSetKey>;
	template
	class NE_DLL NETLimitedArgument<NEInt64SetKey>;
	template
	class NE_DLL NETLimitedArgument<NEFloatSetKey>;
	template
	class NE_DLL NETLimitedArgument<NEDoubleSetKey>;
	template
	class NE_DLL NETLimitedArgument<NEStringSetKey>;
	template
	class NE_DLL NETLimitedArgument<NEWStringSetKey>;
	template
	class NE_DLL NETLimitedArgument<NEModuleCodeSetKey>;
	template
	class NE_DLL NETLimitedArgument<NENodeCodeSetKey>;
	template
	class NE_DLL NETSelectorArgument<NENodeSelector>;
	template
	class NE_DLL NETSelectorArgument<NEModuleSelector>;
	template
	class NE_DLL NETSelectorArgument<NEKeySelector>;

	NETArgument<NEKey>::NETArgument(const This& rhs)
		: Super(rhs)
	{

	}

	NETArgument<NEKey>::NETArgument()
		: Super(/*NEType::NEKEY*/)
	{

	}

	const NEKey& NETArgument<NEKey>::getDefaultKey() const
	{
		This* unconsted = const_cast<This*>(this);

		return unconsted->getDefaultKey();
	}

	NEKey& NETArgument<NEKey>::getDefaultKey()
	{
		static NEIntKey _default_key;

		return _default_key;
	}
}
#pragma warning(pop)