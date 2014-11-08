#pragma once

#include "../../../Modules/NEObject/NEObject.hpp"
#include "../../Templates/NEEnlistableSetTemplate/NEEnlistableSetTempate.hpp"

namespace NE
{
	class NEEnlistableManager;

	class NE_DLL NEBinderBase : public NEObject
	{
		typedef NEBinderBase ThisClass;
		typedef NEObject SuperClass;

	public:
		ThisClass();
		ThisClass(const ThisClass& source);

	public:
		virtual ~NEBinderBase();

	public:
		const ThisClass& operator=(const ThisClass& source);
		bool operator==(const ThisClass& source) const;
		bool operator!=(const ThisClass& source) const;

	public:
		type_index getRealIndex() const;
		type_id getComparingId() const;
		NEEnlistableManager& getManager();
		const NEEnlistableManager& getManager() const;

	public:
		virtual bool isBinded() const;

	public:
		virtual void release();
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual type_result isValid() const;
		virtual NEObject& clone() const;
		virtual NEType::Type getType() const;

	public:
		type_result unbind();

	private:
		const ThisClass& _assign(const ThisClass& source);
		void _release();

	protected:
		type_index _real_index;
		type_id _comparing_id;
		NEType::Type _manager_type;
	};
}