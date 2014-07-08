#pragma once

#include "../../Commons/Templates/NEIndexedArrayTemplate/NEIndexedArrayTemplate.hpp"
#include "../../Commons/Templates/NEEnlistableSetTemplate/NEEnlistableSetTempate.hpp"
#include "../NEModule/NEModule.hpp"

namespace NE
{
	template
	class NE_DLL NEIndexedArrayTemplate<NEModule*, true, NEType::NEINDEXED_MODULESET>;

	template
	class NE_DLL NEEnlistableSetTemplate< NEIndexedArrayTemplate<NEModule*, true, NEType::NEINDEXED_MODULESET> >;

	class NE_DLL NEIndexedModuleSet : public NEEnlistableSetTemplate< NEIndexedArrayTemplate<NEModule*, true, NEType::NEINDEXED_MODULESET> >
	{
		typedef NEIndexedModuleSet ThisClass;
		typedef NEEnlistableSetTemplate< NEIndexedArrayTemplate<NEModule*, true, NEType::NEINDEXED_MODULESET> > SuperClass;

	public:
		NEIndexedModuleSet(NEEnlistableManager& manager);
		NEIndexedModuleSet(type_count size);
		NEIndexedModuleSet(const NEIndexedModuleSet& source);

	public:
		virtual ~NEIndexedModuleSet();

	public:
		const NEIndexedModuleSet& operator+=(const NEIndexedModuleSet& source);
		NEIndexedModuleSet operator+(const NEIndexedModuleSet& source) const;		

	public:
		using SuperClass::insert;
		virtual type_index insert(type_index index, const NEModule* const source);
		virtual type_result setElement(type_index index, const NEModule* const source);
		using SuperClass::setElement;
		virtual type_result resize(type_index new_size);

	public:
		virtual NEType::Type getType() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEObject& clone() const;

	public:
		type_id peekLastGeneratedId() const;

	protected:
		virtual type_result _onEnlisted();

	protected:
		static type_id _generateId();

	protected:
		static type_id _last_generated_id;
	};
}