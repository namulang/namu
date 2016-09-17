#pragma once

#include "../NEUnit/NEUnit.hpp"

namespace NE
{
	class NE_DLL NEBinderBase : public NEUnit
	{
		NE_DECLARE_INTERFACE(NEBinderBase, NEUnit)
		
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
		NEUnit& get();
		const NEUnit& get() const;
		type_id getBindedId() const;
		type_bool isBinded() const;

	public:
		virtual void release();
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual type_result isValid() const;

	protected:
		type_result _bind(const NEUnit& target);

	protected:
		type_id _binded_id;
	};
}