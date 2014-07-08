#pragma once

#include "../NEKeyBinder/NEKeyBinder.hpp"
#include "../../Typedefs/NETString/NETString.hpp"

namespace NE
{
	class NE_DLL NEKeyNameBinder : public NEKeyBinder
	{
	public:
		typedef NEKeyNameBinder ThisClass;
		typedef NEKeyBinder SuperClass;

	public:
		NEKeyNameBinder();
		NEKeyNameBinder(const NETString& new_keyname);

	public:
		const NETString& getKeyName() const;
		type_result setKeyName(const NETString& new_keyname);

	public:
		type_result bind();

	public:
		virtual void release()
		{
			_keyname.release();
			SuperClass::release();
		}
		virtual type_result isValid() const
		{
			type_result result = 0;
			if(result = _keyname.isValid())	return result;

			return SuperClass::isValid();
		}
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
		{
			SuperClass::serialize(loader);

			return loader >> _keyname;
		}
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
		{
			SuperClass::serialize(saver);

			return saver << _keyname;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		virtual NEType::Type getType() const
		{
			return NEType::NEKEY_NAME_BINDER;
		}

	private:
		NETString _keyname;
	};
}