#pragma once

#include "../NEModule/NEModule.hpp"
#include "../NETVector/NETVector.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<NEModule*, true, NEModule*>;
	
	class NEModuleSet : public NETVector<NEModule*, true, NEModule*>
	{
		typedef NETVector<NEModule*, true, NEModule*> _Super;

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