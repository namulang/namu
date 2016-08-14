#pragma once

#include "../NESwitchableUnit/NESwitchableUnit.hpp"
#include "../NETEnlistableSet/NETEnlistableSet.hpp"

namespace NE
{
	class NEEnlistableManager;

	class NE_DLL NEBinderBase : public NESwitchableUnit
	{
		NE_DECLARE_INTERFACE(NEBinderBase, NESwitchableUnit)
		
	public:
		NEBinderBase();
		NEBinderBase(const This& source);

	public:
		virtual ~NEBinderBase();

	public:
		const This& operator=(const This& source);
		type_bool operator==(const This& source) const;
		type_bool operator!=(const This& source) const;

	public:
		virtual type_result unbind();

	public:
		type_index getRealIndex() const;
		type_id getComparingId() const;
		NEEnlistableManager& getManager();
		const NEEnlistableManager& getManager() const;

	public:
		virtual type_bool isBinded() const;

	public:
		virtual void release();
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual type_result isValid() const;

	private:
		const This& _assign(const This& source);
		void _release();

	protected:
		type_index _real_index;
		type_id _comparing_id;
		//NEType::Type _manager_type;
	};
}