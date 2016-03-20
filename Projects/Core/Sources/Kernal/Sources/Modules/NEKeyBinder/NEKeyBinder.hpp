#pragma once

#include "../NEBinderBase/NEBinderBase.hpp"

namespace NE
{
	class NEIndexedKeySet;
	class NEKey;

	class NE_DLL NEKeyBinder : public NEBinderBase
	{
		NE_DECLARE_CLASS(NEKeyBinder, NEBinderBase)
	
	public:
		template <typename ModuleSelector, NEType::Type type>
		friend class NETKeySelector;

	public:
		virtual bool isBinded() const;

	public:
		NEKey& getBinded();
		const NEKey& getBinded() const;
		type_result bind(const NEKey& key, NEType::Type manager_type);
		type_bool isBindedLocalKey() const;

	protected:
		type_result _markToBindLocalKey();

	private:
		NEIndexedKeySet& _getKeySet();
		const NEIndexedKeySet& _getKeySet() const;
		type_result _onEnlisted();
	};
}