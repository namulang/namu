#pragma once

#include "../../Commons/Templates/NEIndexedArrayTemplate/NEIndexedArrayTemplate.hpp"
#include "../../Commons/Templates/NEEnlistableSetTemplate/NEEnlistableSetTempate.hpp"
#include "../NENode/NENode.hpp"

namespace NE
{
	template
	class NE_DLL NEIndexedArrayTemplate<NENode*, true, NEType::NEINDEXED_NODESET>;

	template 
	class NE_DLL NEEnlistableSetTemplate< NEIndexedArrayTemplate<NENode*, true, NEType::NEINDEXED_NODESET> >;

	class NE_DLL NEIndexedNodeSet : public NEEnlistableSetTemplate< NEIndexedArrayTemplate<NENode*, true, NEType::NEINDEXED_NODESET> >
	{
		typedef NEIndexedNodeSet ThisClass;
		typedef NEEnlistableSetTemplate< NEIndexedArrayTemplate<NENode*, true, NEType::NEINDEXED_NODESET> > SuperClass;

	public:
		NEIndexedNodeSet(NEEnlistableManager& manager);
		NEIndexedNodeSet(type_count size);
		NEIndexedNodeSet(const NEIndexedNodeSet& source);

	public:
		virtual ~NEIndexedNodeSet();
	public:
		const NEIndexedNodeSet& operator+=(const NEIndexedNodeSet& source);
		NEIndexedNodeSet operator+(const NEIndexedNodeSet& source) const;		

	public:
		using SuperClass::insert;
		virtual type_index insert(type_index index, const NENode* const source);
		virtual type_result setElement(type_index index, const NENode* const source);
		using SuperClass::setElement;
		virtual type_result remove(type_index index);
		virtual type_result resize(type_index index);

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