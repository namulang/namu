#pragma once

#include "../../Functions/NEResult/NEResult.hpp"

namespace NE
{
	class NEEnlistableManager;

	class NE_DLL NEGlobalManagerOffer
	{
		friend class NENodeArray;
		friend class NEModuleArray;
		friend class NEKeyArray;

	public:
		static NEEnlistableManager& getGlobalManager();

	protected:
		static type_result _setGlobalManager(NEEnlistableManager& new_manager);

	private:
		static NEEnlistableManager* _global_manager;
	};
}