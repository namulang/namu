#pragma once

#include "../NEModule/NEModule.hpp"
#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<NEModule*, true, NEModule*, NEType::NEMODULESET>;
	
	class NEModuleSet : public NETArray<NEModule*, true, NEModule*, NEType::NEMODULESET>
	{
	public:
		typedef NEModuleSet ThisClass;
		typedef NETArray<NEModule*, true, NEModule*, NEType::NEMODULESET> SuperClass;

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