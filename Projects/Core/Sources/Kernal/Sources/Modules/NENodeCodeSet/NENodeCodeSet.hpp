#pragma once

#include "../../Commons/Templates/NEEnlistableSetTemplate/NEEnlistableSetTempate.hpp"
#include "../../Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"
#include "../NENode/NENode.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<type_code, false, NENode, NEType::NENODE_CODESET>;
	template
	class NE_DLL NEEnlistableSetTemplate< NEArrayTemplate<type_code, false, NENode, NEType::NENODE_CODESET> >;

	class NE_DLL NENodeCodeSet : public NEEnlistableSetTemplate< NEArrayTemplate<type_code, false, NENode, NEType::NENODE_CODESET> >, public NEExecutable
	{
	public:
		typedef NEEnlistableSetTemplate< NEArrayTemplate<type_code, false, NENode, NEType::NENODE_CODESET> > SuperClass;
		typedef NENodeCodeSet ThisClass;
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
		virtual type_index find(const NENode& source) const;
		virtual type_result resize(type_index new_size);

	public:
		virtual void release();
		virtual NEObject& clone() const;
		virtual NEType::Type getType() const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		using SuperClass::serialize;

	protected:
		virtual type_result _onEnlisted();

	protected:
		virtual type_result _onEnlisted(NENode& node);

	protected:
		NEIndexedNodeSet& _getNodeSet();
		const NEIndexedNodeSet& _getNodeSet() const;
		const NENodeCodeSet& _assign(const NENodeCodeSet& source);
	};
}