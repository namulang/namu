#pragma once

#include "../NETIndexedArray/NETIndexedArray.hpp"
#include "../NETEnlistableSet/NETEnlistableSet.hpp"
#include "../NEKey/NEKey.hpp"

namespace NE
{
	template
	class NE_DLL NETIndexedArray<NEKey*, true, NEType::NEINDEXED_KEYSET>;

	template
	class NE_DLL NETEnlistableSet< NETIndexedArray<NEKey*, true, NEType::NEINDEXED_KEYSET> >;

	class NE_DLL NEIndexedKeySet : public NETEnlistableSet< NETIndexedArray<NEKey*, true, NEType::NEINDEXED_KEYSET> >
	{
		typedef NEIndexedKeySet ThisClass;
		typedef NETEnlistableSet< NETIndexedArray<NEKey*, true, NEType::NEINDEXED_KEYSET> > SuperClass;

	public:
		NEIndexedKeySet(NEEnlistableManager& manager);
		NEIndexedKeySet(type_count size);
		NEIndexedKeySet(const NEIndexedKeySet& source);

	public:
		virtual ~NEIndexedKeySet();

	public:
		const NEIndexedKeySet& operator+=(const NEIndexedKeySet& source);
		NEIndexedKeySet operator+(const NEIndexedKeySet& source) const;
		
	public:
		using SuperClass::insert;
		virtual type_index insert(type_index index, const NEKey* const source);
		virtual type_result setElement(type_index index, const NEKey* const source);
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