#pragma once

#include "../NEKeyBinder/NEKeyBinder.hpp"
#include "../NETString/NETString.hpp"

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
		NEKeyNameBinder(const ThisClass& rhs);

	public:
		const NETString& getKeyName() const;
		type_result setKeyName(const NETString& new_keyname);

	public:
		NEKeyNameBinder& operator=(const NEKeyNameBinder& rhs);
		bool operator==(const NEKeyNameBinder& rhs) const;
		bool operator!=(const NEKeyNameBinder& rhs) const;

	public:
		virtual type_result bind();

	public:
		virtual void release();
		virtual type_result isValid() const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEObject& clone() const;
		virtual NEType::Type getType() const;

	private:
		NEKeyNameBinder& _assign(const ThisClass& rhs);
		type_result _bindLocalKey();

	private:
		NETString _keyname;
	};
}