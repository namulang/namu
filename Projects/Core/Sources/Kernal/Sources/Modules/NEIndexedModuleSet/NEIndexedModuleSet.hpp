#pragma once

#include "../NETIndexedArray/NETIndexedArray.hpp"
#include "../NETEnlistableSet/NETEnlistableSet.hpp"
#include "../NEModule/NEModule.hpp"

namespace NE
{
	template
	class NE_DLL NETIndexedArray<NEModule*, true>;

	template
	class NE_DLL NETEnlistableSet< NETIndexedArray<NEModule*, true> >;

	class NE_DLL NEIndexedModuleSet : public NETEnlistableSet< NETIndexedArray<NEModule*, true> >
	{
		typedef NETEnlistableSet< NETIndexedArray<NEModule*, true> > _Super;

		NE_DECLARE_CLASS(NEIndexedModuleSet, _Super)

	public:
		NEIndexedModuleSet(NEEnlistableManager& manager);
		NEIndexedModuleSet(type_count size);
		NEIndexedModuleSet(const This& source);

	public:
		virtual ~NEIndexedModuleSet();

	public:
		const This& operator+=(const This& source);
		This operator+(const This& source) const;		

	public:
		using Super::insert;
		virtual type_index insert(type_index index, const NEModule* const source);
		virtual type_result setElement(type_index index, const NEModule* const source);
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