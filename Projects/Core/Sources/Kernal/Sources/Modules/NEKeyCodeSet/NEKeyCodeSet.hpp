#pragma once

#include "../NETVector/NETVector.hpp"
#include "../NETEnlistableSet/NETEnlistableSet.hpp"
#include "../NETString/NETString.hpp"
#include "../NEKey/NEKey.hpp"

namespace NE
{
	class NEIndexedKeySet;
	template
	class NE_DLL NETVector<type_code, false, NEKey>;
	template
	class NE_DLL NETEnlistableSet< NETVector<type_code, false, NEKey> >;

	class NE_DLL NEKeyCodeSet : public NETEnlistableSet< NETVector<type_code, false, NEKey> >
	{
		typedef NETEnlistableSet<NETVector<type_code, false, NEKey>> _Super;

		NE_DECLARE_CLASS(NEKeyCodeSet, _Super)

	public:
		typedef type_code InnerTrait;
		typedef NEKey OuterTrait;

	public:
		friend class NEIndexedModuleSet;
		friend class NENode;

	public:
		NEKeyCodeSet();
		NEKeyCodeSet(type_index size);
		NEKeyCodeSet(const This& source);

	public:
		virtual ~NEKeyCodeSet();

	public:
		const NEKeyCodeSet& operator+=(const This& source);
		NEKeyCodeSet operator+(const This& source) const;

	public:
		virtual type_index insert(type_index, const NEKey& source);
		virtual type_index remove(type_index index);
		virtual type_result resize(type_index new_size);

	public:
		virtual NEKey& getElement(type_index index);
		virtual const NEKey& getElement(type_index index) const;
		virtual type_result setElement(type_index index, const NEKey& source);
		virtual type_index match(const NEKey& source) const;

	public:
		virtual void release();

	protected:
		virtual type_result _onEnlisted();
		type_result _onEnlisted(NEKey& key);

	protected:
		NEIndexedKeySet& _getKeySet();
		const NEIndexedKeySet& _getKeySet() const;
		const This& _assign(const This& source);
	};
}