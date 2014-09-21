#pragma once

#include "../NEModule/NEModule.hpp"
#include "../NEKeySet/NEKeySet.hpp"

namespace NE
{
	class NE_DLL NEKeyManager : public NEModule
	{
	public:
		bool operator==(const NEKeyManager& source) const;
		bool operator!=(const NEKeyManager& source) const;

	public:
		const NEKey& getKey(NEType::Type type) const;
		const NEKey& getKey(const NEString& type_name) const;
		const NEKeySet& getKeySet() const;

	public:
		virtual type_result initialize();
		virtual const NEExportable::ModuleHeader& getHeader() const;
		
	private:
		type_result execute();

	public:
		virtual NEType::Type getType() const;
		virtual NEObject& clone() const;

	protected:
		NEKeySet _keyset;
	};
}