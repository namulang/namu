#pragma once

#include "../../Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"
#include "../../Commons/Templates/NEEnlistableSetTemplate/NEEnlistableSetTempate.hpp"
#include "../NETString/NETString.hpp"
#include "../NEKey/NEKey.hpp"

namespace NE
{
	class NEIndexedKeySet;
	template
	class NE_DLL NEArrayTemplate<type_code, false, NEKey, NEType::NEKEY_CODESET>;
	template
	class NE_DLL NEEnlistableSetTemplate< NEArrayTemplate<type_code, false, NEKey, NEType::NEKEY_CODESET> >;

	class NE_DLL NEKeyCodeSet : public NEEnlistableSetTemplate< NEArrayTemplate<type_code, false, NEKey, NEType::NEKEY_CODESET> >
	{
	public:
		typedef NEEnlistableSetTemplate< NEArrayTemplate<type_code, false, NEKey, NEType::NEKEY_CODESET> > SuperClass;
		typedef NEKeyCodeSet ThisClass;
		typedef type_code InnerType;
		typedef NEKey OuterType;

	public:
		friend class NEIndexedModuleSet;
		friend class NENode;

	public:
		NEKeyCodeSet();
		NEKeyCodeSet(type_index size);
		NEKeyCodeSet(const NEKeyCodeSet& source);

	public:
		virtual ~NEKeyCodeSet();

	public:
		const NEKeyCodeSet& operator+=(const NEKeyCodeSet& source);
		NEKeyCodeSet operator+(const NEKeyCodeSet& source) const;

	public:
		virtual type_index insert(type_index, const NEKey& source);
		virtual type_index remove(type_index index);
		virtual type_result resize(type_index new_size);

	public:
		virtual NEKey& getElement(type_index index);
		virtual const NEKey& getElement(type_index index) const;
		virtual type_result setElement(type_index index, const NEKey& source);
		virtual type_index find(const NEKey& source) const;

	public:
		virtual void release();
		virtual NEObject& clone() const;
		virtual NEType::Type getType() const;

	protected:
		virtual type_result _onEnlisted();
		type_result _onEnlisted(NEKey& key);

	protected:
		NEIndexedKeySet& _getKeySet();
		const NEIndexedKeySet& _getKeySet() const;
		const NEKeyCodeSet& _assign(const NEKeyCodeSet& source);
	};
}