#pragma once

#include "../NEModule/NEModule.hpp"
#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<NEModule*, true, NEModule*>;
	
	class NEModuleSet : public NETArray<NEModule*, true, NEModule*>
	{
		typedef NETArray<NEModule*, true, NEModule*> _Super;

		NE_DECLARE_CLASS(NEModuleSet, _Super)

	public:
		NEModuleSet();
		NEModuleSet(type_count size);
		NEModuleSet(const This& rhs);

	public:
		virtual ~NEModuleSet();

	public:
		virtual type_index insert(type_index index, const NEModule* const source);
		virtual type_result setElement(type_index index, const NEModule* const source);

	private:
		void _updateModule(type_index index);
	};
}