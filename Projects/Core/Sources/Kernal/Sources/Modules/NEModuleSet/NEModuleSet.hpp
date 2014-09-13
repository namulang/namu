#pragma once

#include "../NEModule/NEModule.hpp"
#include "../../Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<NEModule*, true, NEModule*, NEType::NEMODULESET>;
	
	class NEModuleSet : public NEArrayTemplate<NEModule*, true, NEModule*, NEType::NEMODULESET>
	{
	public:
		typedef NEModuleSet ThisClass;
		typedef NEArrayTemplate<NEModule*, true, NEModule*, NEType::NEMODULESET> SuperClass;

	public:
		NEModuleSet();
		NEModuleSet(type_count size);
		NEModuleSet(const NEModuleSet& rhs);

	public:
		virtual ~NEModuleSet();

	public:
		virtual type_index insert(type_index index, const NEModule* const source);
		virtual type_result setElement(type_index index, const NEModule* const source);

	private:
		void _updateModule(type_index index);
	};
}