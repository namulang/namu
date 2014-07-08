#pragma once

#include "../../Commons/Templates/NEEnlistableSetTemplate/NEEnlistableSetTempate.hpp"
#include "../../Commons/Templates/NEListTemplate/NEListTemplate.hpp"
#include "../NENode/NENode.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<type_code, false, NENode, NEType::NENODE_CODESET>;
	template
	class NE_DLL NEEnlistableSetTemplate< NEArrayTemplate<type_code, false, NENode, NEType::NENODE_CODESET> >;

	class NE_DLL NENodeCodeSet : public NEEnlistableSetTemplate< NEArrayTemplate<type_code, false, NENode, NEType::NENODE_CODESET> >, public NEExecutable
	{
		typedef NEEnlistableSetTemplate< NEArrayTemplate<type_code, false, NENode, NEType::NENODE_CODESET> > SuperClass;
		typedef NENodeCodeSet ThisClass;

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

	public:
		virtual NEObject& clone() const;
		virtual void release();
		virtual NEType::Type getType() const;

	protected:
		virtual type_result _onEnlisted()
		{
			type_result result = RESULT_SUCCESS;
			for(int n=0; n < getLength() ;n++)
				result |= _onEnlisted(getElement(n));

			return result;
		}

	protected:
		type_result _onEnlisted(NENode& node)
		{
			node._manager = &getManager();
			return node._onEnlisted();
		}

	protected:
		NEIndexedNodeSet& _getNodeSet();
		const NEIndexedNodeSet& _getNodeSet() const;
	};
}