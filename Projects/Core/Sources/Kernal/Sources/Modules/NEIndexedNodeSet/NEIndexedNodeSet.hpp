#pragma once

#include "../NETIndexedArray/NETIndexedArray.hpp"
#include "../NETEnlistableSet/NETEnlistableSet.hpp"
#include "../NENode/NENode.hpp"

namespace NE
{
	template
	class NE_DLL NETIndexedArray<NENode*, true>;

	template 
	class NE_DLL NETEnlistableSet< NETIndexedArray<NENode*, true> >;

	class NE_DLL NEIndexedNodeSet : public NETEnlistableSet< NETIndexedArray<NENode*, true> >
	{
		typedef NETEnlistableSet< NETIndexedArray<NENode*, true> > _Super;
		//	Why should this class be declared as Interface, not TConcreteClass?:
		//		NEIndexedNodeSet has no constructor that doesn't need parameter.
		NE_DECLARE_INTERFACE(NEIndexedNodeSet, _Super)

	public:
		NEIndexedNodeSet(NEEnlistableManager& manager);
		NEIndexedNodeSet(type_count size);
		NEIndexedNodeSet(const This& source);

	public:
		virtual ~NEIndexedNodeSet();
	public:
		const This& operator+=(const This& source);
		This operator+(const This& source) const;		

	public:
		using Super::insert;
		virtual type_index insert(type_index index, const NENode* const source);
		virtual type_result setElement(type_index index, const NENode* const source);
		using Super::setElement;
		virtual type_result remove(type_index index);
		virtual type_result resize(type_index index);

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