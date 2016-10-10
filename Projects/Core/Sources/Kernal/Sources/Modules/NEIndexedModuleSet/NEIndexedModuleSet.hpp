#pragma once

#include "../NETArray/NETArray.hpp"
#include "../NETEnlistableSet/NETEnlistableSet.hpp"
#include "../NEModule/NEModule.hpp"

namespace NE
{
	template
	class NE_DLL NETDeeper<NETArray<NEModule>>;

	template
	class NE_DLL NETEnlistableSet< NETDeeper<NETArray<NEModule>> >;

	class NE_DLL NEIndexedModuleSet : public NETEnlistableSet< NETDeeper<NETArray<NEModule>> >
	{
		typedef NETEnlistableSet< NETDeeper<NETArray<NEModule>> > _Super;
		//	Why should this class be declared as Interface, not TConcreteClass?:
		//		this has no constructor that doesn't need parameter.
		NE_DECLARE_INTERFACE(NEIndexedModuleSet, _Super)

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