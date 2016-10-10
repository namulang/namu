#pragma once

#include "../NETEnlistableSet/NETEnlistableSet.hpp"
#include "../NETVector/NETVector.hpp"
#include "../NENode/NENode.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<type_code, false, NENode>;
	template
	class NE_DLL NETEnlistableSet< NETVector<type_code, false, NENode> >;

	class NE_DLL NENodeCodeSet : public NETEnlistableSet< NETVector<type_code, false, NENode> >, public NEExecutable
	{
		typedef NETVector<type_code, false, NENode> _Type;

		NE_DECLARE_CLASS(NENodeCodeSet, NETEnlistableSet<_Type>)

	public:
		typedef type_code InnerType;
		typedef NENode OuterType;

		friend class NEKeyCodeSet;

	public:
		NENodeCodeSet();
		NENodeCodeSet(type_index size);
		NENodeCodeSet(const NENodeCodeSet& source);

	public:
		virtual ~NENodeCodeSet();

	public:
		const NENodeCodeSet& operator+=(const NENodeCodeSet& source);
		NENodeCodeSet operator+(const NENodeCodeSet& source) const;

	public:
		virtual type_result execute();

	public:
		virtual type_index insert(type_index, const NENode& source);
		virtual type_index remove(type_index index);

	public:
		virtual NENode& getElement(type_index index);
		virtual const NENode& getElement(type_index index) const;
		virtual type_result setElement(type_index index, const NENode& source);
		virtual type_index match(const NENode& source) const;
		virtual type_result resize(type_index new_size);

	public:
		virtual void release();
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		using Super::serialize;

	protected:
		virtual type_result _onEnlisted();

	protected:
		virtual type_result _onEnlisted(NENode& node);

	protected:
		NENodeArray& _getNodeSet();
		const NENodeArray& _getNodeSet() const;
		const NENodeCodeSet& _assign(const NENodeCodeSet& source);
	};
}