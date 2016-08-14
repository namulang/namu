#pragma once

#include "../NEModule/NEModule.hpp"
#include "../NEKeySet/NEKeySet.hpp"

namespace NE
{
	class NE_DLL NEKeyManager : public NEModule
	{
		NE_DECLARE_MODULE(NEKeyManager, NEModule)

	public:
		type_bool operator==(const This& source) const;
		type_bool operator!=(const This& source) const;

	public:
		//const NEKey& getKey(NEType::Type type) const;
		const NEKey& getKey(const NEString& type_name) const;
		const NEKeySet& getKeySet() const;

	public:
		virtual type_result initialize();
		virtual const NEExportable::ModuleHeader& getHeader() const;
		
	private:
		type_result execute();

	protected:
		NEKeySet _keyset;
	};
}