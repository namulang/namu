#include "NEGlobalManagerOffer.hpp"
#include "../../../Modules/NEEnlistableManager/NEEnlistableManager.hpp"

namespace NE
{
	NEEnlistableManager* NEGlobalManagerOffer::_global_manager = NE_NULL;

	NEEnlistableManager& NE::NEGlobalManagerOffer::getGlobalManager()
	{
		return *_global_manager;
	}

	type_result NE::NEGlobalManagerOffer::_setGlobalManager(NEEnlistableManager& new_manager)
	{
		_global_manager = &new_manager;

		return RESULT_SUCCESS;
	}
}