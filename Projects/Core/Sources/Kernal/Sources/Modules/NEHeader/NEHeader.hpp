#pragma once

#include "../NEIdentifier/NEIdentifier.hpp"

namespace NE
{
	class NE_DLL NEHeader : public NEIdentifier
	{
		NE_DECLARE_CLASS_ONLY(NEHeader, NEIdentifier)

		//	constructors:
	public:
		NEHeader();
		NEHeader(	const NETString& new_name, const NETString& new_author, type_count new_revision_count, type_count new_version_count, 
					const NETString& new_comment, const NETString& new_version, const NETString& new_release_date						);
		NEHeader(const This& rhs);

	public:
		virtual ~NEHeader();

	public:
		This& operator=(const This& rhs);
		type_bool operator==(const This& rhs) const;
		type_bool operator!=(const This& rhs) const;

	public:
		const NETString& getComment() const;
		NETString& getComment();
		const NETString& getVersion() const;
		NETString& getVersion();
		const NETString& getReleaseDate() const;
		NETString& getReleaseDate();

	public:
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual type_result isValid() const;

	private:
		This& _assign(const This& rhs);
		void _release();

	private:
		NETString _comment;
		NETString _version;
		NETString _release_date;
	};
}