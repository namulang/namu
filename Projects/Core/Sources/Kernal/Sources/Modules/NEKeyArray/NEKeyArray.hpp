#pragma once

#include "../NETArray/NETArray.hpp"
#include "../NETEnlistableSet/NETEnlistableSet.hpp"
#include "../NETDeeper/NETDeeper.hpp"
#include "../NEKey/NEKey.hpp"

namespace NE
{
	template
	class NE_DLL NETDeeper<NETArray<NEKey>>;

	template
	class NE_DLL NETEnlistableSet< NETDeeper<NETArray<NEKey>> >;

	class NE_DLL NEKeyArray : public NETEnlistableSet< NETDeeper<NETArray<NEKey>> >
	{
		typedef NETEnlistableSet< NETDeeper<NETArray<NEKey>> > _Super;
		//	Why should this class be declared as Interface, not TConcreteClass?:
		//		this has no constructor that doesn't need parameter.
		NE_DECLARE_INTERFACE(NEKeyArray, _Super)

	public:
		NEKeyArray(NEEnlistableManager& manager);
		NEKeyArray(type_count size);
		NEKeyArray(const This& source);

	public:
		virtual ~NEKeyArray();

	public:
		const NEKeyArray& operator+=(const This& source);
		NEKeyArray operator+(const This& source) const;
		
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