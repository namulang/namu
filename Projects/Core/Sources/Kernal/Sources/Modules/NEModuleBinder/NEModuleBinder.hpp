#pragma once

#include "../NEBinderBase/NEBinderBase.hpp"

namespace NE
{
	class NEIndexedModuleSet;
	class NEModule;

	class NE_DLL NEModuleBinder : public NEBinderBase
	{
		typedef NEModuleBinder ThisClass;
		typedef NEBinderBase SuperClass;

		template <typename NodeSelector, NEType::Type type>
		friend class NEModuleSelectorTemplate;
	public:
		NEModuleBinder();
		NEModuleBinder(const NEModule& module, NEType::Type manager_type);

	public:
		virtual bool isBinded() const;

	public:
		virtual NEObject& clone() const;
		virtual NEType::Type getType() const;

	public:
		NEModule& getBinded();
		const NEModule& getBinded() const;
		type_result bind(const NEModule& module, NEType::Type manager_type);

	private:
		NEIndexedModuleSet& _getModuleSet();
		const NEIndexedModuleSet& _getModuleSet() const;
	};
}