#pragma once

#include "../NETIndexedArray/NETIndexedArray.hpp"
#include "../NETEnlistableSet/NETEnlistableSet.hpp"
#include "../NEKey/NEKey.hpp"

namespace NE
{
	template
	class NE_DLL NETIndexedArray<NEKey*, true>;

	template
	class NE_DLL NETEnlistableSet< NETIndexedArray<NEKey*, true> >;

	class NE_DLL NEIndexedKeySet : public NETEnlistableSet< NETIndexedArray<NEKey*, true> >
	{
		typedef NETEnlistableSet< NETIndexedArray<NEKey*, true> > _Super;

		NE_DECLARE_CLASS(NEIndexedKeySet, _Super)

	public:
		NEIndexedKeySet(NEEnlistableManager& manager);
		NEIndexedKeySet(type_count size);
		NEIndexedKeySet(const This& source);

	public:
		virtual ~NEIndexedKeySet();

	public:
		const NEIndexedKeySet& operator+=(const This& source);
		NEIndexedKeySet operator+(const This& source) const;
		
	public:
		using Super::insert;
		virtual type_index insert(type_index index, const NEKey* const source);
		virtual type_result setElement(type_index index, const NEKey* const source);
		using Super::setElement;
		virtual type_result resize(type_index new_size);

	public:
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

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