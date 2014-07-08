#pragma once

#include "../../Functions/NEResult/NEResult.hpp"

namespace NE
{
	class NEEnlistableManager;

	class NE_DLL NEGlobalManagerOffer
	{
		friend class NEIndexedNodeSet;
		friend class NEIndexedModuleSet;
		friend class NEIndexedKeySet;

	public:
		static NEEnlistableManager& getGlobalManager();

	protected:
		static type_result _setGlobalManager(NEEnlistableManager& new_manager);

	private:
		static NEEnlistableManager* _global_manager;
	};
}