#pragma once

#include "../NEModule/NEModule.hpp"
#include "../NETVector/NETVector.hpp"
#include "../NETDeeper/NETDeeper.hpp"

namespace NE
{
	template
	class NE_DLL NETDeeper<NETVector<NEModule>>;
	
	class NEModuleSet : public NETDeeper<NETVector<NEModule>>
	{
		typedef NETDeeper<NETVector<NEModule>> _Super;

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