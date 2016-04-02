#pragma once

#include "../NEIdentifier/NEIdentifier.hpp"

namespace NE
{
	class NE_DLL NEClassIdentifier : public NEIdentifier
	{
		NE_DECLARE_CLASS(NEClassIdentifier, NEIdentifier)

	public:
		NEClassIdentifier();
		NEClassIdentifier(const NETString& name, const NETString& author, type_int new_interface_revision, const NETString& class_name);
		NEClassIdentifier(const NEPackage& package, const NETString& new_classname);
		NEClassIdentifier(const This& rhs);

	public:
		virtual ~NEClassIdentifier();

	public:
		const This& operator=(const This& source);
		bool operator==(const This& source) const;
		bool operator!=(const This& source) const;

	public:
		const NETString& getClassName() const;
		NETString& getClassName();

	public:
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual type_result isValid() const;

	private:
		NETString _classname;
	};
}