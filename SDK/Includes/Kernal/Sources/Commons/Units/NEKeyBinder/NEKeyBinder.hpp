#pragma once

#include "../NEBinderBase/NEBinderBase.hpp"

namespace NE
{
	class NEIndexedKeySet;
	class NEKey;

	class NE_DLL NEKeyBinder : public NEBinderBase
	{
		typedef NEKeyBinder ThisClass;
		typedef NEBinderBase SuperClass;

		template <typename ModuleSelector, NEType::Type type>
		friend class NEKeySelectorTemplate;

	public:
		virtual bool isBinded() const;

	public:
		virtual NEObject& clone() const;
		virtual NEType::Type getType() const;

	public:
		NEKey& getBinded();
		const NEKey& getBinded() const;
		type_result bind(const NEKey& key, NEType::Type manager_type);

	private:
		NEIndexedKeySet& _getKeySet();
		const NEIndexedKeySet& _getKeySet() const;
		type_result _onEnlisted();
	};
}