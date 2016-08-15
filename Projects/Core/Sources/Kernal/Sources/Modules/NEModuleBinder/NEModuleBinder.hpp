#pragma once

#include "../NEBinderBase/NEBinderBase.hpp"

namespace NE
{
	class NEIndexedModuleSet;
	class NEModule;

	class NE_DLL NEModuleBinder : public NEBinderBase
	{
		NE_DECLARE_CLASS(NEModuleBinder, NEBinderBase)

		template <typename NodeSelector>
		friend class NETModuleSelector;
	public:
		NEModuleBinder();
		NEModuleBinder(const NEModule& module, NEType::Type manager_type);

	public:
		virtual type_bool isBinded() const;

	public:
		NEModule& getBinded();
		const NEModule& getBinded() const;
		type_result bind(const NEModule& module, NEType::Type manager_type);

	private:
		NEIndexedModuleSet& _getModuleSet();
		const NEIndexedModuleSet& _getModuleSet() const;
	};
}